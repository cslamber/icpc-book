import sys,os,re
bookpath = sys.argv[1]

included = set()
def include(file):
    file = file.strip()
    if file in included: return ""
    included.add(file)
    return open(os.path.join(bookpath, file)).read()

def aggregate(desc):
    return ""

fs = {"include": include, "aggregate": aggregate}


data = open(0).read()
while True:
    res = re.search(r"/\*\* (\S+)(.+?)\*/", data)
    if res is None: break
    data = "\n".join([data[:res.start()], fs[res[1].lower()](res[2]), data[res.end():]])

print(data)

