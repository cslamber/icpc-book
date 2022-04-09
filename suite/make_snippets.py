from sys import argv
from pathlib import Path
import json

book_path = Path(argv[1])

print(json.dumps({
	f"C++ Book: {f.stem.lower()}": {
		"prefix": f"BOOK_{f.stem.upper()}"
		"body": f"""
#pragma region {f.stem.lower()}
{f.read_text().replace("$","\\$")}
#pragma endregion
""".strip(),
		"description": f"Raw text from {f.relative_to(book_path)}",
	}
	for f in book_path.glob("**/*.hpp")
})
