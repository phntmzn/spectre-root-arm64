# reporter.py
"""Small helpers for emitting JSON reports."""
import json
from pathlib import Path
from typing import Any


def write_report(path: str, findings: list[dict[str, Any]]) -> None:
    """Write findings as pretty-printed UTF-8 JSON."""
    destination = Path(path)
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(
        json.dumps(findings, indent=2, ensure_ascii=False) + "\n",
        encoding="utf-8",
    )
