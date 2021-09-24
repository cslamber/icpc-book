import http.server,string,json,os
from pathlib import Path

archive_dir = Path(os.environ["ARCHIVEPATH"])
book_dir = Path(os.environ["BOOKPATH"])

address = ('localhost', 27121)

allowed = string.ascii_letters + string.digits + "-()=_+*[];: "

def slugify(text):
    return ''.join(x for x in text if x in allowed).strip()

class Handler(http.server.BaseHTTPRequestHandler):
    def do_POST(self):
        assert self.client_address[0] == '127.0.0.1'
        data = json.load(self.rfile)
        group = slugify(data['group'])
        name = slugify(data['name'])
        base = archive_dir / group / name
        tests = base / 'tests'
        Path.mkdir(tests, parents=True, exist_ok=False)
        for i,sample in enumerate(data.get('tests', [])):
            try:
                cur = tests / f"sample-{i+1}"
                Path.mkdir(cur)
                with open(os.path.join(cur, 'in.txt'), 'w') as f:
                    f.write(sample['input'])
                with open(os.path.join(cur, 'out.txt'), 'w') as f:
                    f.write(sample['output'])
            except:
                pass
        os.chdir(base)
        os.system('make >/dev/null')
        print(base)


http.server.HTTPServer(address, Handler).serve_forever()
