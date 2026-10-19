# test_analyzer.py
import json
import tempfile
import unittest
from pathlib import Path

from spectreroot.analyzer import load_report, summarize


class AnalyzerTests(unittest.TestCase):
    def test_load_and_summarize(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "report.json"
            path.write_text(json.dumps([{"title": "Example", "severity": "low"}]))
            report = load_report(str(path))
            self.assertEqual(len(report), 1)
            self.assertIn("[LOW] Example", summarize(report))

    def test_single_object_is_accepted(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "report.json"
            path.write_text(json.dumps({"path": "/tmp/example"}))
            self.assertEqual(len(load_report(str(path))), 1)


if __name__ == "__main__":
    unittest.main()
