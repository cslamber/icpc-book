import sys,os,re

bookpath = sys.argv[1]

data = open(0).read()

included = set()

while True:
    res = re.search(r"// INCLUDE ([^\n\t ]+)\n", data)
    if res is None: break
    if res[1] in included: continue
    included.add(res[1])
    with open(os.path.join(bookpath, res[1])) as f:
        data = data[:res.start()] + f.read() + data[res.end()-1:]

print(data)

