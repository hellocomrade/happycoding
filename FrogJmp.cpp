int solutionFrogJmp(int X, int Y, int D) {
    assert(X>0);
    assert(D>0);
    assert(X <= Y);
    int steps = (Y - X) / D;
    if (steps*D<Y - X)++steps;
    return steps;
}
