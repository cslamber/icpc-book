import http.server, string, json, os

archive_dir = Path(os.environ["ARCHIVEPATH"])
book_dir = Path(os.environ["BOOKPATH"])

address = ('localhost', 27121)
