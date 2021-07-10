tcT struct flist {
    struct elem { T hd; shared_ptr<elem> tl; };
    using sp = shared_ptr<elem>;

    sp v;
    flist() {}
    flist(T hd, flist tl) : v(new elem{hd, tl.v}) {}

    flist operator>>(T hd) const { return flist(hd, *this); }

    vec<T> to_vec() const {
        vec<T> r;
        for (sp c = v; c; c = c->tl)
            r.push_back(c->hd);
        return r;
    }
};
