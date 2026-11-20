#!/usr/bin/env python3
"""Regression tests for Skell Silence's installable-artifact visibility policy."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
WORKFLOW_PATH = ROOT / ".github" / "workflows" / "build.yml"


def step_blocks(text: str):
    starts = list(re.finditer(r"(?m)^      - (?:name:|uses:)", text))
    return [
        text[match.start():starts[index + 1].start() if index + 1 < len(starts) else len(text)]
        for index, match in enumerate(starts)
    ]


class ReleaseArtifactVisibilityTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.workflow = WORKFLOW_PATH.read_text(encoding="utf-8")
        cls.steps = step_blocks(cls.workflow)

    def find_step(self, marker: str) -> str:
        matches = [step for step in self.steps if marker in step]
        self.assertEqual(len(matches), 1, f"Expected exactly one workflow step containing {marker!r}")
        return matches[0]

    def test_installable_product_upload_is_private_only(self):
        step = self.find_step("name: SkellSilence-Windows")
        self.assertIn("uses: actions/upload-artifact@v6", step)
        self.assertRegex(step, r"(?m)^        if: github\.event\.repository\.private == true$")

    def test_public_repository_emits_withholding_notice(self):
        step = self.find_step("Withhold installable preview artifact in public repositories")
        self.assertRegex(step, r"(?m)^        if: always\(\) && github\.event\.repository\.private != true$")
        self.assertIn("::notice::", step)
        self.assertIn("GITHUB_STEP_SUMMARY", step)
        self.assertIn("SkellSilence-UI-QA", step)

    def test_ui_diagnostics_remain_independent_of_product_visibility(self):
        step = self.find_step("name: SkellSilence-UI-QA")
        self.assertIn("uses: actions/upload-artifact@v6", step)
        self.assertRegex(step, r"(?m)^        if: always\(\)$")
        self.assertNotIn("github.event.repository.private", step)

    def test_release_manifest_records_visibility_policy(self):
        self.assertIn("productArtifactVisibilityPolicy = 'PRIVATE_REPOSITORY_ONLY'", self.workflow)


if __name__ == "__main__":
    unittest.main()
