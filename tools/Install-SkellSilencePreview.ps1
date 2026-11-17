[CmdletBinding(SupportsShouldProcess = $true, ConfirmImpact = 'High')]
param(
    [ValidateSet('Install', 'Rollback', 'SelfTest')]
    [string]$Action = 'Install',
    [string]$PackageRoot = $PSScriptRoot,
    [string]$InstallRoot,
    [string]$BackupRoot
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$script:ProductName = 'Skell Silence'
$script:BundleName = 'Skell Silence.vst3'
$script:BundleId = 'uno.skellyr.silence'
$script:ManufacturerCode = 'SkAu'
$script:PluginCode = 'Sl01'
$script:AudioCid = 'ABCDEF019182FAEB536B4175536C3031'
$script:ControllerCid = 'ABCDEF011234ABCD536B4175536C3031'

function Get-FullPath {
    param([Parameter(Mandatory)][string]$Path)
    return [IO.Path]::GetFullPath($Path)
}

function Write-Utf8NoBom {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$Text
    )
    $encoding = New-Object -TypeName System.Text.UTF8Encoding -ArgumentList $false
    [IO.File]::WriteAllText($Path, $Text, $encoding)
}

function Get-Sha256 {
    param([Parameter(Mandatory)][string]$Path)
    return (Get-FileHash -LiteralPath $Path -Algorithm SHA256).Hash.ToLowerInvariant()
}

function Get-TreeDigest {
    param([Parameter(Mandatory)][string]$Path)
    $root = Get-FullPath $Path
    if (-not (Test-Path -LiteralPath $root -PathType Container)) {
        throw "Bundle directory is missing: $root"
    }
    $files = @(Get-ChildItem -LiteralPath $root -Recurse -File | Sort-Object FullName)
    if ($files.Count -eq 0) {
        throw "Bundle contains no files: $root"
    }
    $rows = foreach ($file in $files) {
        $relative = $file.FullName.Substring($root.Length).TrimStart([char[]]@([char]92, [char]47)).Replace('\', '/')
        "$relative  $(Get-Sha256 $file.FullName)"
    }
    $bytes = [Text.Encoding]::UTF8.GetBytes(($rows -join [Environment]::NewLine))
    $sha = [Security.Cryptography.SHA256]::Create()
    try {
        return ([BitConverter]::ToString($sha.ComputeHash($bytes))).Replace('-', '').ToLowerInvariant()
    }
    finally {
        $sha.Dispose()
    }
}

function Test-PathWithinRoot {
    param(
        [Parameter(Mandatory)][string]$Path,
        [Parameter(Mandatory)][string]$Root
    )
    $rootFull = Get-FullPath $Root
    $pathFull = Get-FullPath $Path
    $prefix = $rootFull.TrimEnd([char[]]@([char]92, [char]47)) + [IO.Path]::DirectorySeparatorChar
    return $pathFull.StartsWith($prefix, [StringComparison]::OrdinalIgnoreCase)
}

function Assert-WindowsPe32Plus {
    param([Parameter(Mandatory)][string]$Path)
    $bytes = [IO.File]::ReadAllBytes($Path)
    if ($bytes.Length -lt 0x100 -or $bytes[0] -ne 0x4d -or $bytes[1] -ne 0x5a) {
        throw 'VST3 module is not a valid Windows PE image'
    }
    $peOffset = [BitConverter]::ToInt32($bytes, 0x3c)
    if ($peOffset -lt 0x40 -or $peOffset + 26 -gt $bytes.Length) {
        throw 'VST3 module has an invalid PE header offset'
    }
    if ([BitConverter]::ToUInt32($bytes, $peOffset) -ne 0x4550) {
        throw 'VST3 module is missing the PE signature'
    }
    if ([BitConverter]::ToUInt16($bytes, $peOffset + 4) -ne 0x8664) {
        throw 'VST3 module is not AMD64'
    }
    if ([BitConverter]::ToUInt16($bytes, $peOffset + 24) -ne 0x20b) {
        throw 'VST3 module is not PE32+'
    }
}

function Get-BundleDetails {
    param([Parameter(Mandatory)][string]$BundlePath)
    $bundle = Get-FullPath $BundlePath
    if (-not (Test-Path -LiteralPath $bundle -PathType Container)) {
        throw "VST3 bundle directory is missing: $bundle"
    }

    $contents = Join-Path $bundle 'Contents'
    $metadataPath = Join-Path $contents 'Resources/moduleinfo.json'
    $modulePath = Join-Path $contents 'x86_64-win/Skell Silence.vst3'
    if (-not (Test-Path -LiteralPath $metadataPath -PathType Leaf)) {
        throw 'VST3 moduleinfo.json is missing'
    }
    if (-not (Test-Path -LiteralPath $modulePath -PathType Leaf)) {
        throw 'Windows x86_64 VST3 module is missing'
    }

    $modules = @(Get-ChildItem -LiteralPath $contents -Recurse -File -Filter '*.vst3')
    if ($modules.Count -ne 1 -or
        (Get-FullPath $modules[0].FullName) -cne (Get-FullPath $modulePath)) {
        throw "Expected exactly one Windows VST3 module under Contents; found $($modules.Count)"
    }
    Assert-WindowsPe32Plus -Path $modulePath

    $metadata = [IO.File]::ReadAllText($metadataPath, [Text.Encoding]::UTF8) | ConvertFrom-Json -ErrorAction Stop
    if ($metadata.Name -cne $script:ProductName) {
        throw "Unexpected VST3 product name: $($metadata.Name)"
    }
    if ([string]::IsNullOrWhiteSpace([string]$metadata.Version)) {
        throw 'VST3 metadata version is empty'
    }
    $factory = $metadata.'Factory Info'
    if ($null -eq $factory -or $factory.Vendor -cne 'Skell Audio') {
        throw 'VST3 vendor metadata does not match Skell Audio'
    }

    $classes = @($metadata.Classes)
    if ($classes.Count -ne 2) {
        throw "Expected exactly two protected VST3 classes, found $($classes.Count)"
    }
    $audio = @($classes | Where-Object { $_.Category -eq 'Audio Module Class' })
    $controller = @($classes | Where-Object { $_.Category -eq 'Component Controller Class' })
    if ($audio.Count -ne 1 -or $controller.Count -ne 1) {
        throw 'VST3 metadata must contain one audio class and one controller class'
    }
    if ([string]$audio[0].CID -cne $script:AudioCid -or
        [string]$controller[0].CID -cne $script:ControllerCid) {
        throw 'VST3 class IDs do not match the protected v2.8 identity'
    }
    foreach ($class in $classes) {
        if ($class.Name -cne $script:ProductName -or
            $class.Vendor -cne 'Skell Audio' -or
            $class.Version -cne $metadata.Version) {
            throw 'VST3 class name, vendor, or version does not match the bundle'
        }
    }

    return [pscustomobject]@{
        BundlePath = $bundle
        ModulePath = $modulePath
        MetadataPath = $metadataPath
        Metadata = $metadata
        Version = [string]$metadata.Version
        ModuleSha256 = Get-Sha256 $modulePath
        MetadataSha256 = Get-Sha256 $metadataPath
        TreeSha256 = Get-TreeDigest $bundle
    }
}

function Write-PackageChecksums {
    param([Parameter(Mandatory)][string]$Root)
    $rootFull = Get-FullPath $Root
    $checksumPath = Join-Path $rootFull 'SHA256SUMS.txt'
    $files = @(Get-ChildItem -LiteralPath $rootFull -Recurse -File |
        Where-Object { (Get-FullPath $_.FullName) -cne (Get-FullPath $checksumPath) } |
        Sort-Object FullName)
    if ($files.Count -eq 0) {
        throw 'Cannot create package checksums for an empty directory'
    }
    $lines = foreach ($file in $files) {
        $relative = $file.FullName.Substring($rootFull.Length).TrimStart([char[]]@([char]92, [char]47)).Replace('\', '/')
        "$(Get-Sha256 $file.FullName)  $relative"
    }
    [IO.File]::WriteAllLines($checksumPath, [string[]]$lines, [Text.Encoding]::ASCII)
}

function Get-PackageInfo {
    param([Parameter(Mandatory)][string]$Root)
    $rootFull = Get-FullPath $Root
    $manifestPath = Join-Path $rootFull 'release-manifest.json'
    $checksumsPath = Join-Path $rootFull 'SHA256SUMS.txt'
    $installerPath = Join-Path $rootFull 'Install-SkellSilencePreview.ps1'
    $guidePath = Join-Path $rootFull 'INSTALL-PREVIEW.txt'
    $bundlePath = Join-Path $rootFull $script:BundleName

    foreach ($required in @($manifestPath, $checksumsPath, $installerPath, $guidePath, $bundlePath)) {
        if (-not (Test-Path -LiteralPath $required)) {
            throw "Preview package is incomplete; missing: $required"
        }
    }

    $bundles = @(Get-ChildItem -LiteralPath $rootFull -Directory -Filter '*.vst3')
    if ($bundles.Count -ne 1 -or (Get-FullPath $bundles[0].FullName) -cne (Get-FullPath $bundlePath)) {
        throw "Preview package must contain exactly one '$($script:BundleName)' bundle"
    }

    $manifest = [IO.File]::ReadAllText($manifestPath, [Text.Encoding]::UTF8) | ConvertFrom-Json -ErrorAction Stop
    if ($manifest.product -cne $script:ProductName -or
        $manifest.distribution -cne 'Windows VST3 x64' -or
        $manifest.releaseStatus -cne 'PREVIEW_ONLY' -or
        $manifest.commercialReleaseEligible -ne $false) {
        throw 'Package is not a Skell Silence Windows preview-only release'
    }
    if ($manifest.installer.file -cne 'Install-SkellSilencePreview.ps1' -or
        $manifest.installer.sha256 -cne (Get-Sha256 $installerPath)) {
        throw 'Installer file does not match the release manifest'
    }

    $bundle = Get-BundleDetails -BundlePath $bundlePath
    if ($manifest.version -cne $bundle.Version -or
        $manifest.bundle.name -cne $script:BundleName -or
        $manifest.bundle.vendor -cne 'Skell Audio' -or
        $manifest.bundle.platformFolder -cne 'x86_64-win' -or
        $manifest.bundle.moduleSha256 -cne $bundle.ModuleSha256 -or
        $manifest.bundle.moduleInfoSha256 -cne $bundle.MetadataSha256 -or
        $manifest.bundle.bundleId -cne $script:BundleId -or
        $manifest.bundle.manufacturerCode -cne $script:ManufacturerCode -or
        $manifest.bundle.pluginCode -cne $script:PluginCode) {
        throw 'Package manifest does not match the VST3 bundle identity or hashes'
    }
    $manifestIds = @($manifest.bundle.classIds | ForEach-Object { [string]$_ } | Sort-Object)
    $expectedIds = @($script:AudioCid, $script:ControllerCid) | Sort-Object
    if (($manifestIds -join '|') -cne ($expectedIds -join '|')) {
        throw 'Package manifest class IDs do not match the protected VST3 identity'
    }

    $listed = @{}
    foreach ($line in [IO.File]::ReadAllLines($checksumsPath)) {
        if ($line -notmatch '^([0-9a-fA-F]{64})\s{2}(.+)$') {
            throw "Malformed SHA256SUMS entry: $line"
        }
        $expectedHash = $Matches[1].ToLowerInvariant()
        $relative = $Matches[2].Trim()
        if ($listed.ContainsKey($relative)) {
            throw "Duplicate SHA256SUMS path: $relative"
        }
        $target = Join-Path $rootFull ($relative.Replace('/', [IO.Path]::DirectorySeparatorChar))
        if (-not (Test-PathWithinRoot -Path $target -Root $rootFull) -or
            -not (Test-Path -LiteralPath $target -PathType Leaf)) {
            throw "SHA256SUMS path is missing or escapes the package: $relative"
        }
        if ((Get-Sha256 $target) -cne $expectedHash) {
            throw "SHA256 mismatch: $relative"
        }
        $listed[$relative] = $true
    }

    $actualFiles = @(Get-ChildItem -LiteralPath $rootFull -Recurse -File |
        Where-Object { (Get-FullPath $_.FullName) -cne (Get-FullPath $checksumsPath) })
    if ($actualFiles.Count -ne $listed.Count) {
        throw 'SHA256SUMS does not cover every package file exactly once'
    }
    foreach ($file in $actualFiles) {
        $relative = $file.FullName.Substring($rootFull.Length).TrimStart([char[]]@([char]92, [char]47)).Replace('\', '/')
        if (-not $listed.ContainsKey($relative)) {
            throw "Package file is not covered by SHA256SUMS: $relative"
        }
    }

    return [pscustomobject]@{
        Root = $rootFull
        BundlePath = $bundlePath
        Version = $bundle.Version
        ModuleSha256 = $bundle.ModuleSha256
        TreeSha256 = $bundle.TreeSha256
        Manifest = $manifest
    }
}

function Resolve-InstallRoot {
    param([string]$Requested)
    if (-not [string]::IsNullOrWhiteSpace($Requested)) {
        return Get-FullPath $Requested
    }
    if ([string]::IsNullOrWhiteSpace($env:LOCALAPPDATA)) {
        throw 'LOCALAPPDATA is unavailable; pass -InstallRoot explicitly'
    }
    return Get-FullPath (Join-Path $env:LOCALAPPDATA 'Programs/Common/VST3')
}

function Resolve-BackupRoot {
    param([string]$Requested)
    if (-not [string]::IsNullOrWhiteSpace($Requested)) {
        return Get-FullPath $Requested
    }
    if ([string]::IsNullOrWhiteSpace($env:LOCALAPPDATA)) {
        throw 'LOCALAPPDATA is unavailable; pass -BackupRoot explicitly'
    }
    return Get-FullPath (Join-Path $env:LOCALAPPDATA 'SkellAudio/Backups/Skell Silence')
}

function New-Backup {
    param(
        [Parameter(Mandatory)][string]$SourceBundle,
        [Parameter(Mandatory)][string]$BackupRootPath,
        [Parameter(Mandatory)][string]$InstallRootPath,
        [Parameter(Mandatory)][ValidateSet('install-rollback', 'rollback-safety')][string]$Kind
    )
    New-Item -ItemType Directory -Path $BackupRootPath -Force | Out-Null
    $stamp = (Get-Date).ToUniversalTime().ToString('yyyyMMddTHHmmssfffZ')
    $folder = Join-Path $BackupRootPath ($stamp + '-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Path $folder -Force | Out-Null
    $backupBundle = Join-Path $folder $script:BundleName

    try {
        Copy-Item -LiteralPath $SourceBundle -Destination $backupBundle -Recurse -ErrorAction Stop
        $sourceDigest = Get-TreeDigest $SourceBundle
        $backupDigest = Get-TreeDigest $backupBundle
        if ($sourceDigest -cne $backupDigest) {
            throw 'Backup verification failed; the installed bundle was not changed'
        }
        $version = 'unknown'
        try { $version = (Get-BundleDetails -BundlePath $SourceBundle).Version } catch { }
        $backupManifest = [ordered]@{
            schemaVersion = 1
            product = $script:ProductName
            kind = $Kind
            createdUtc = (Get-Date).ToUniversalTime().ToString('o')
            installRoot = (Get-FullPath $InstallRootPath)
            bundleName = $script:BundleName
            version = $version
            treeSha256 = $sourceDigest
        }
        Write-Utf8NoBom -Path (Join-Path $folder 'backup-manifest.json') -Text ($backupManifest | ConvertTo-Json -Depth 6)
        return [pscustomobject]@{ Folder = $folder; Version = $version; TreeSha256 = $sourceDigest }
    }
    catch {
        if (Test-Path -LiteralPath $folder) {
            Remove-Item -LiteralPath $folder -Recurse -Force -ErrorAction SilentlyContinue
        }
        throw
    }
}

function Install-VerifiedBundle {
    param(
        [Parameter(Mandatory)][string]$SourceBundle,
        [Parameter(Mandatory)][string]$InstallRootPath
    )
    New-Item -ItemType Directory -Path $InstallRootPath -Force | Out-Null
    $destination = Join-Path $InstallRootPath $script:BundleName
    $stage = Join-Path $InstallRootPath ('.Skell Silence.stage-' + [guid]::NewGuid().ToString('N'))
    $previous = Join-Path $InstallRootPath ('.Skell Silence.previous-' + [guid]::NewGuid().ToString('N'))
    $sourceDigest = Get-TreeDigest $SourceBundle
    $movedPrevious = $false

    try {
        Copy-Item -LiteralPath $SourceBundle -Destination $stage -Recurse -ErrorAction Stop
        if ((Get-TreeDigest $stage) -cne $sourceDigest) {
            throw 'Staged VST3 bundle hash mismatch; refusing installation'
        }
        $null = Get-BundleDetails -BundlePath $stage
        if (Test-Path -LiteralPath $destination) {
            Move-Item -LiteralPath $destination -Destination $previous -ErrorAction Stop
            $movedPrevious = $true
        }
        try {
            Move-Item -LiteralPath $stage -Destination $destination -ErrorAction Stop
        }
        catch {
            if ($movedPrevious -and -not (Test-Path -LiteralPath $destination) -and
                (Test-Path -LiteralPath $previous)) {
                Move-Item -LiteralPath $previous -Destination $destination -ErrorAction Stop
                $movedPrevious = $false
            }
            throw
        }
        if ($movedPrevious -and (Test-Path -LiteralPath $previous)) {
            Remove-Item -LiteralPath $previous -Recurse -Force -ErrorAction SilentlyContinue
        }
        return $destination
    }
    finally {
        if (Test-Path -LiteralPath $stage) {
            Remove-Item -LiteralPath $stage -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
}

function Invoke-Install {
    param(
        [Parameter(Mandatory)][string]$PackageRootPath,
        [Parameter(Mandatory)][string]$InstallRootPath,
        [Parameter(Mandatory)][string]$BackupRootPath
    )
    $package = Get-PackageInfo -Root $PackageRootPath
    $destination = Join-Path $InstallRootPath $script:BundleName
    $backup = $null
    if (Test-Path -LiteralPath $destination) {
        $backup = New-Backup -SourceBundle $destination -BackupRootPath $BackupRootPath -InstallRootPath $InstallRootPath -Kind 'install-rollback'
    }
    $installedPath = Install-VerifiedBundle -SourceBundle $package.BundlePath -InstallRootPath $InstallRootPath
    return [pscustomobject]@{
        Version = $package.Version
        InstallPath = $installedPath
        BackupFolder = if ($null -ne $backup) { $backup.Folder } else { $null }
    }
}

function Get-BackupCandidates {
    param(
        [Parameter(Mandatory)][string]$BackupRootPath,
        [Parameter(Mandatory)][string]$InstallRootPath
    )
    $candidates = @()
    if (-not (Test-Path -LiteralPath $BackupRootPath -PathType Container)) {
        return @()
    }
    foreach ($folder in Get-ChildItem -LiteralPath $BackupRootPath -Directory) {
        $manifestPath = Join-Path $folder.FullName 'backup-manifest.json'
        if (-not (Test-Path -LiteralPath $manifestPath -PathType Leaf)) {
            continue
        }
        try {
            $manifest = [IO.File]::ReadAllText($manifestPath, [Text.Encoding]::UTF8) | ConvertFrom-Json -ErrorAction Stop
            if ($manifest.kind -ne 'install-rollback' -or
                $manifest.installRoot -ine (Get-FullPath $InstallRootPath) -or
                ($manifest.PSObject.Properties.Name -contains 'restoredUtc')) {
                continue
            }
            $candidates += [pscustomobject]@{
                Folder = $folder.FullName
                ManifestPath = $manifestPath
                Manifest = $manifest
            }
        }
        catch {
            Write-Warning "Skipping unreadable backup manifest: $manifestPath"
        }
    }
    return @($candidates | Sort-Object { $_.Manifest.createdUtc } -Descending)
}

function Invoke-Rollback {
    param(
        [Parameter(Mandatory)][string]$InstallRootPath,
        [Parameter(Mandatory)][string]$BackupRootPath
    )
    $destination = Join-Path $InstallRootPath $script:BundleName
    $candidates = @(Get-BackupCandidates -BackupRootPath $BackupRootPath -InstallRootPath $InstallRootPath)
    if ($candidates.Count -eq 0) {
        throw 'No unused verified install backup exists for this VST3 install path'
    }

    $selected = $candidates[0]
    $backupBundle = Join-Path $selected.Folder $script:BundleName
    if (-not (Test-Path -LiteralPath $backupBundle -PathType Container) -or
        (Get-TreeDigest $backupBundle) -cne $selected.Manifest.treeSha256) {
        throw 'The selected rollback backup is missing or has a SHA-256 mismatch'
    }
    $details = Get-BundleDetails -BundlePath $backupBundle

    if (Test-Path -LiteralPath $destination) {
        $null = New-Backup -SourceBundle $destination -BackupRootPath $BackupRootPath -InstallRootPath $InstallRootPath -Kind 'rollback-safety'
    }
    $installedPath = Install-VerifiedBundle -SourceBundle $backupBundle -InstallRootPath $InstallRootPath
    $selected.Manifest | Add-Member -NotePropertyName restoredUtc -NotePropertyValue ((Get-Date).ToUniversalTime().ToString('o'))
    Write-Utf8NoBom -Path $selected.ManifestPath -Text ($selected.Manifest | ConvertTo-Json -Depth 6)

    return [pscustomobject]@{
        Version = $details.Version
        InstallPath = $installedPath
        RestoredFrom = $selected.Folder
    }
}

function New-TestPackage {
    param(
        [Parameter(Mandatory)][string]$Root,
        [Parameter(Mandatory)][string]$Version,
        [Parameter(Mandatory)][byte]$VersionByte,
        [int]$Machine = 0x8664
    )
    New-Item -ItemType Directory -Path $Root -Force | Out-Null
    $bundle = Join-Path $Root $script:BundleName
    $modulePath = Join-Path $bundle 'Contents/x86_64-win/Skell Silence.vst3'
    $metadataPath = Join-Path $bundle 'Contents/Resources/moduleinfo.json'
    New-Item -ItemType Directory -Path (Split-Path -Parent $modulePath) -Force | Out-Null
    New-Item -ItemType Directory -Path (Split-Path -Parent $metadataPath) -Force | Out-Null

    $pe = New-Object byte[] 512
    $pe[0] = 0x4d
    $pe[1] = 0x5a
    [Array]::Copy([BitConverter]::GetBytes([int]0x80), 0, $pe, 0x3c, 4)
    $pe[0x80] = 0x50
    $pe[0x81] = 0x45
    $pe[0x82] = 0
    $pe[0x83] = 0
    [Array]::Copy([BitConverter]::GetBytes([UInt16]$Machine), 0, $pe, 0x84, 2)
    [Array]::Copy([BitConverter]::GetBytes([UInt16]0x20b), 0, $pe, 0x98, 2)
    $pe[0x100] = $VersionByte
    [IO.File]::WriteAllBytes($modulePath, $pe)

    $metadata = [ordered]@{
        Name = $script:ProductName
        Version = $Version
        'Factory Info' = [ordered]@{ Vendor = 'Skell Audio'; URL = ''; 'E-Mail' = '' }
        Classes = @(
            [ordered]@{ CID = $script:AudioCid; Name = $script:ProductName; Category = 'Audio Module Class'; Vendor = 'Skell Audio'; Version = $Version }
            [ordered]@{ CID = $script:ControllerCid; Name = $script:ProductName; Category = 'Component Controller Class'; Vendor = 'Skell Audio'; Version = $Version }
        )
    }
    Write-Utf8NoBom -Path $metadataPath -Text ($metadata | ConvertTo-Json -Depth 8)

    Copy-Item -LiteralPath $PSCommandPath -Destination (Join-Path $Root 'Install-SkellSilencePreview.ps1') -Force
    Write-Utf8NoBom -Path (Join-Path $Root 'INSTALL-PREVIEW.txt') -Text 'Synthetic self-test package. Not a real plugin binary.'
    $moduleHash = Get-Sha256 $modulePath
    $metadataHash = Get-Sha256 $metadataPath
    $installerHash = Get-Sha256 (Join-Path $Root 'Install-SkellSilencePreview.ps1')
    $manifest = [ordered]@{
        schemaVersion = 1
        product = $script:ProductName
        version = $Version
        distribution = 'Windows VST3 x64'
        releaseStatus = 'PREVIEW_ONLY'
        commercialReleaseEligible = $false
        bundle = [ordered]@{
            name = $script:BundleName
            module = 'Skell Silence.vst3'
            platformFolder = 'x86_64-win'
            moduleSha256 = $moduleHash
            moduleInfoSha256 = $metadataHash
            vendor = 'Skell Audio'
            bundleId = $script:BundleId
            manufacturerCode = $script:ManufacturerCode
            pluginCode = $script:PluginCode
            classIds = @($script:AudioCid, $script:ControllerCid)
        }
        installer = [ordered]@{
            file = 'Install-SkellSilencePreview.ps1'
            sha256 = $installerHash
        }
    }
    Write-Utf8NoBom -Path (Join-Path $Root 'release-manifest.json') -Text ($manifest | ConvertTo-Json -Depth 10)
    Write-PackageChecksums -Root $Root
}

function Invoke-SelfTest {
    $root = Join-Path ([IO.Path]::GetTempPath()) ('SkellSilenceInstallerSelfTest-' + [guid]::NewGuid().ToString('N'))
    $packageA = Join-Path $root 'package-a'
    $packageB = Join-Path $root 'package-b'
    $packageBadArch = Join-Path $root 'package-bad-arch'
    $installRootPath = Join-Path $root 'user-vst3'
    $backupRootPath = Join-Path $root 'backups'

    try {
        New-TestPackage -Root $packageA -Version '2.8.0' -VersionByte 1
        New-TestPackage -Root $packageB -Version '2.8.1' -VersionByte 2
        Invoke-Install -PackageRootPath $packageA -InstallRootPath $installRootPath -BackupRootPath $backupRootPath | Out-Null
        $installed = Get-BundleDetails -BundlePath (Join-Path $installRootPath $script:BundleName)
        if ($installed.Version -cne '2.8.0') {
            throw 'Self-test failed: first preview install did not produce v2.8.0'
        }

        Invoke-Install -PackageRootPath $packageB -InstallRootPath $installRootPath -BackupRootPath $backupRootPath | Out-Null
        $installed = Get-BundleDetails -BundlePath (Join-Path $installRootPath $script:BundleName)
        if ($installed.Version -cne '2.8.1') {
            throw 'Self-test failed: second preview install did not produce v2.8.1'
        }
        $candidates = @(Get-BackupCandidates -BackupRootPath $backupRootPath -InstallRootPath $installRootPath)
        if ($candidates.Count -ne 1 -or $candidates[0].Manifest.version -cne '2.8.0') {
            throw 'Self-test failed: previous version was not backed up and indexed'
        }

        Invoke-Rollback -InstallRootPath $installRootPath -BackupRootPath $backupRootPath | Out-Null
        $installed = Get-BundleDetails -BundlePath (Join-Path $installRootPath $script:BundleName)
        if ($installed.Version -cne '2.8.0') {
            throw 'Self-test failed: rollback did not restore v2.8.0'
        }
        if (@(Get-BackupCandidates -BackupRootPath $backupRootPath -InstallRootPath $installRootPath).Count -ne 0) {
            throw 'Self-test failed: restored rollback point was not retired'
        }

        $before = Get-TreeDigest (Join-Path $installRootPath $script:BundleName)
        $tamperedModule = Join-Path $packageB ($script:BundleName + '/Contents/x86_64-win/Skell Silence.vst3')
        $tamperedBytes = [IO.File]::ReadAllBytes($tamperedModule)
        $tamperedBytes[0x101] = 0x7f
        [IO.File]::WriteAllBytes($tamperedModule, $tamperedBytes)
        $failedClosed = $false
        try {
            Invoke-Install -PackageRootPath $packageB -InstallRootPath $installRootPath -BackupRootPath $backupRootPath | Out-Null
        }
        catch {
            $failedClosed = $true
        }
        if (-not $failedClosed -or (Get-TreeDigest (Join-Path $installRootPath $script:BundleName)) -cne $before) {
            throw 'Self-test failed: tampered package changed the installed plugin'
        }

        New-TestPackage -Root $packageBadArch -Version '2.8.2' -VersionByte 3 -Machine 0x014c
        $failedClosed = $false
        try {
            Invoke-Install -PackageRootPath $packageBadArch -InstallRootPath $installRootPath -BackupRootPath $backupRootPath | Out-Null
        }
        catch {
            $failedClosed = $true
        }
        if (-not $failedClosed -or (Get-TreeDigest (Join-Path $installRootPath $script:BundleName)) -cne $before) {
            throw 'Self-test failed: non-AMD64 package changed the installed plugin'
        }

        Write-Host 'PASS: preview install, verified backup, rollback, checksum rejection, and PE32+ architecture rejection'
    }
    finally {
        if (Test-Path -LiteralPath $root) {
            Remove-Item -LiteralPath $root -Recurse -Force -ErrorAction SilentlyContinue
        }
    }
}

switch ($Action) {
    'SelfTest' {
        Invoke-SelfTest
    }
    'Install' {
        $resolvedInstallRoot = Resolve-InstallRoot $InstallRoot
        $resolvedBackupRoot = Resolve-BackupRoot $BackupRoot
        $package = Get-PackageInfo -Root $PackageRoot
        $destination = Join-Path $resolvedInstallRoot $script:BundleName
        if ($PSCmdlet.ShouldProcess($destination, "Install preview v$($package.Version) with verified backup")) {
            $result = Invoke-Install -PackageRootPath $PackageRoot -InstallRootPath $resolvedInstallRoot -BackupRootPath $resolvedBackupRoot
            Write-Host "Installed Skell Silence preview v$($result.Version) at $($result.InstallPath)"
            if ($result.BackupFolder) {
                Write-Host "Previous version preserved at $($result.BackupFolder)"
            }
        }
    }
    'Rollback' {
        $resolvedInstallRoot = Resolve-InstallRoot $InstallRoot
        $resolvedBackupRoot = Resolve-BackupRoot $BackupRoot
        $destination = Join-Path $resolvedInstallRoot $script:BundleName
        if ($PSCmdlet.ShouldProcess($destination, 'Restore the most recent unused verified backup')) {
            $result = Invoke-Rollback -InstallRootPath $resolvedInstallRoot -BackupRootPath $resolvedBackupRoot
            Write-Host "Rolled back Skell Silence to v$($result.Version) at $($result.InstallPath)"
            Write-Host "Restored from $($result.RestoredFrom)"
        }
    }
}
