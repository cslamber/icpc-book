import os,re,sys
bookpath = os.environ['BOOKPATH']
assert bookpath

included = set()
def include(file):
    file = os.path.realpath(file)
    if file in included: return ""
    included.add(file)
    return open(file).read()

def python(code):
    from io import StringIO
    from contextlib import redirect_stdout

    f = StringIO()
    with redirect_stdout(f):
        exec(code.strip())
    return f.getvalue()

def named(data):
    name,fields,typ=data.strip().split(':',2)
    fields=fields.strip().split()
    name=name.strip()
    typ=typ.strip()
    methods=" ".join(f"auto& {field}() {{ return get<{i}>(*this); }}" for i,field in enumerate(fields))
    return f"struct {name} : public {typ} {{ using {typ}::{typ}; {methods} }};"

fs = {
    "include": (lambda f: include(os.path.join(bookpath, f))),
    "python": python,
    "named": named,
    "linclude": (lambda f: include(os.path.join(os.path.dirname(sys.argv[1]), f)))
    }

data = open(sys.argv[1]).read()
while True:
    res = re.search(r"/\*\* (\S+) (.+?)\*/", data) or re.search(r"/// (\S+) (.+?)\n", data)
    if res is None: break
    data = "\n".join([data[:res.start()], fs[res[1].lower()](res[2]), data[res.end():]])

print(data)
