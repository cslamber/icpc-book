import http.server, string, json, os

PORT = 27121 # from competitive companion

archive_dir = Path(os.environ["ARCHIVEPATH"])
book_dir = Path(os.environ["BOOKPATH"])

address = ('localhost', PORT)
