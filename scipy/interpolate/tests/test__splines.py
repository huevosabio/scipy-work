import numpy as np

from numpy.testing import assert_allclose
from scipy.interpolate._splines import BSpline


class TestBSpline(object):
    def test_simple_eval(self):
        np.random.seed(1234)

        spline = BSpline(t=[0, 0, 0, 1, 2, 3, 4, 4, 4], c=[2, 1, 2, 1, 2, 1, 2, 1, 2], k=2)

        xi = np.random.rand(30)*4
        a = spline(xi)
        b = _naive_eval(xi, spline.t, spline.c, spline.k)
        assert_allclose(a, b)

    def test_simple_eval_complex(self):
        np.random.seed(1234)

        spline = BSpline(t=[0, 0, 0, 1, 2, 3, 4, 4, 4], c=[2, 1, 2, 1, 2j, 1, 2, 1, 2], k=2)

        xi = np.random.rand(30)*4
        a = spline(xi)
        b = _naive_eval(xi, spline.t, spline.c, spline.k)
        assert_allclose(a, b)

    def test_fit_natural(self):
        np.random.seed(1234)

        n = 170
        x = np.linspace(0, 1, n)**2
        x.sort()

        ys = [
            np.random.rand(n),
            np.random.rand(n) + 1j*np.random.rand(n),
            np.random.rand(n, 1, 2, 3, 4, 1)
        ]

        for k in range(3, 3+2):
            for y in ys:
                msg = "k=%d, y: %r %r" % (k, y.dtype, y.shape)
                spl = BSpline.fit_free(x, y, k=k)
                assert_allclose(spl(x), y, err_msg=msg)
                assert_allclose(spl(x[1] + 1e-13, k), spl(x[1] - 1e-13, k),
                                rtol=1e-4, atol=1e-4, err_msg=msg)
                assert_allclose(spl(x[-2] + 1e-13, k), spl(x[-2] - 1e-13, k),
                                rtol=1e-4, atol=1e-4, err_msg=msg)


def _naive_B(x, k, i, t):
    """
    Naive way to compute B-spline basis functions. Useful only for testing!
    """

    if k == 0:
        return 1.0 if t[i] <= x < t[i+1] else 0.0

    if t[i+k] == t[i]:
        c1 = 0.0
    else:
        c1 = (x - t[i])/(t[i+k] - t[i]) * _naive_B(x, k-1, i, t)

    if i + k + 1 >= len(t):
        c2 = 0
    elif t[i+k+1] == t[i+1]:
        c2 = 0.0
    else:
        c2 = (t[i+k+1] - x)/(t[i+k+1] - t[i+1]) * _naive_B(x, k-1, i+1, t)

    return (c1 + c2)

def _naive_eval(x, t, c, k):
    """
    Naive B-spline evaluation. Useful only for testing!
    """

    @np.vectorize
    def ev(x):
        i = np.searchsorted(t, x) - 1
        assert t[i] <= x <= t[i+1]
        assert i >= k and i < len(t) - k
        return sum(c[i-j] * _naive_B(x, k, i-j, t) for j in range(0, k+1))

    return ev(x)
