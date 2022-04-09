import http.server, json
from sys import argv
from pathlib import Path

PORT = 27121 # from competitive companion

archive = Path(argv[1])

address = ('localhost', PORT)

allowed = "-()=+*[];:. "
def slugify(s):
	return '_' + ''.join(["_",c][c.isalnum() or c in allowed] for x in s)

class Handler(http.server.BaseHTTPRequestHandler):
	def do_POST(self):
		assert self.client_address[0] == '127.0.0.1'
		data = json.load(self.rfile)
		print(data)
		group = slugify(data['group'])
		name = slugify(data['name'])
		prob = archive / group / name
		print(name, group)
		tests = prob / "tests"
		Path.mkdir(tests, exist_ok=1)
		for i,sample in enumerate(data.get('tests',[])):
			t = tests / f"sample-{i+1}"
			Path.mkdir(t, exist_ok=1)
			(t / "in.txt").write_text(sample['input'].strip())
			(t / "out.txt").write_text(sample['output'].strip())
		(prob / "main.cpp").touch()

http.server.HTTPServer(address, Handler).serve_forever()
