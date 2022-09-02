int tree_h(Tree *tr, int max) {
    int lmax = 0;
    if (tr != NULL) {
        for (int i = 0; i < tr->count; i++) {
            int x = tree_h(tr->sons[i], lmax);
            if (x > lmax) {
                return x;
            }
            return lmax;
        }
    }
    return 0;
}