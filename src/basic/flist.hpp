template<class T>
struct flist_elem {
    shared_ptr<flist_elem> tl;
    T hd;

    flist_elem(T hd, shared_ptr<flist_elem> tl) : hd(hd), tl(tl) {}
};

template<class T>
struct flist : shared_ptr<flist_elem<T>> {
    flist() {}
    flist(shared_ptr<flist_elem<T>> v) : shared_ptr<flist_elem<T>>(v) {}
    flist(T hd, flist tl) : shared_ptr<flist_elem<T>>(new flist_elem<T>(hd, tl)) {}

    vector<T> to_vector() const {
        vector<T> r;
        for (shared_ptr<flist_elem<T>> c = *this; c; c = c->tl)
            r.push_back(c->hd);
        return r;
    }
};