import http.server, string, json, sys, re, subprocess
from configparser import ConfigParser
from pathlib import Path

PORT = 27121 # from competitive companion

passed = Path(sys.argv[2])

address = ('localhost', PORT)

allowed = string.ascii_letters + string.digits + "-()=+*[];:. "
def slugify(s):
	return ('_' if s.startswith('.') else '') + ''.join(x if x in allowed else "_" for x in s)

class Handler(http.server.BaseHTTPRequestHandler):
	def do_POST(self):
		assert self.client_address[0] == '127.0.0.1'
		data = json.load(self.rfile)
		group = slugify(data['group'])
		name = slugify(data['name'])+".base" # needed bc pathlib dumb
		prob = passed / group / name
		print(name, group)
		Path.mkdir(prob.parent, exist_ok=1)
		tests = ConfigParser()
		tests.read_dict({
			f"sample-{i}": {
				'input': "\n"+sample['input'].strip(),
				'output': "\n"+sample['output'].strip(),
			} for i,sample in enumerate(data.get('tests', []))
		})
		tests.write(open(prob.with_suffix(".test_ini"), "x"))
		open(prob.with_suffix('.cpp'), 'x').write(starter)

if sys.argv[1] == "pre":
	body = open(0).read()
	templates = {hpp.stem: hpp for hpp in passed.rglob("*.hpp")}
	used,n=set(),1
	while n:
		body, n = re.subn(
			r'(?m)^/// include (.*)$',
			lambda m: "\n".join(
				used.add(t) or open(templates[t]).read().strip()
				for t in m[1].split() if t not in used),
			body)
	print(body)
elif sys.argv[1] == "listen":
	starter = open(0).read()
	http.server.HTTPServer(address, Handler).serve_forever()
elif sys.argv[1] == "test":
	tests = ConfigParser(comment_prefixes=[])
	tests.read_file(open(0))
	for k,v in tests.items():
		if k == "DEFAULT": continue
		inp=v['input'][1:]
		print(f"Test {k}.\nInput:\n{inp}\nStderr:")
		output = subprocess.check_output(f"'./{passed}'", input=inp, shell=1, text=1)
		print(f"Output:\n{output}")
		print(v['output'].split() == output.split())
