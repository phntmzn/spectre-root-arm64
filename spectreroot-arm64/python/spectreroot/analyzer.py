# analyzer.py
"""Validate and summarize JSON findings produced by local analysis tools.

Expected input: a JSON array of objects, or a single JSON object.
This helper does not execute the inspected files.
"""
import argparse
import json
from pathlib import Path
from typing import Any


def load_report(path: str) -> list[dict[str, Any]]:
    data = json.loads(Path(path).read_text(encoding="utf-8"))
    if isinstance(data, dict):
        data = [data]
    if not isinstance(data, list) or not all(isinstance(item, dict) for item in data):
        raise ValueError("report must be a JSON object or an array of objects")
    return data


def summarize(report: list[dict[str, Any]]) -> str:
    lines = [f"Findings: {len(report)}"]
    for index, item in enumerate(report, start=1):
        title = item.get("title") or item.get("path") or item.get("name") or f"Finding {index}"
        severity = str(item.get("severity", "unspecified")).upper()
        detail = item.get("detail") or item.get("note") or ""
        lines.append(f"{index}. [{severity}] {title}" + (f" — {detail}" if detail else ""))
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description="Summarize a JSON security-analysis report.")
    parser.add_argument("report", help="Path to JSON report file")
    args = parser.parse_args()
    try:
        print(summarize(load_report(args.report)))
    except (OSError, json.JSONDecodeError, ValueError) as exc:
        parser.error(str(exc))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
