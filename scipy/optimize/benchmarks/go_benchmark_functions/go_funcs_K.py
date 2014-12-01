# -*- coding: utf-8 -*-
from __future__ import division, print_function, absolute_import
import numpy as np
from numpy import (abs, arctan2, asarray, cos, exp, floor, log, log10,
                   arange, pi, prod, roll, sign, sin, sqrt, sum, where,
                   zeros, tan, tanh, dot)

from scipy.misc import factorial
from .go_benchmark import Benchmark


class Katsuura(Benchmark):

    """
    Katsuura objective function.

    This class defines the Katsuura global optimization problem. This
    is a multimodal minimization problem defined as follows:

    .. math::

        f_{\\text{Katsuura}}(\\mathbf{x}) = \\prod_{i=0}^{n-1} \\left [ 1 +
        (i+1) \\sum_{k=1}^{d} \\lfloor (2^k x_i) \\rfloor 2^{-k} \\right ]

    Where, in this exercise, :math:`d = 32`.

    Here, :math:`n` represents the number of dimensions and :math:`x_i \\in [0, 100]` for :math:`i=1,...,n`.

    *Global optimum*: :math:`f(x_i) = 1` for :math:`x_i = 0` for :math:`i=1,...,n`.

    """

    def __init__(self, dimensions=2):
        Benchmark.__init__(self, dimensions)

        self._bounds = zip([0.0] * self.N, [100.0] * self.N)

        self.global_optimum = [[0.0 for _ in range(self.N)]]
        self.custom_bounds = [(0, 1), (0, 1)]
        self.fglob = 1.0
        self.change_dimensionality = True

    def fun(self, x, *args):
        self.nfev += 1

        d = 32
        k = np.atleast_2d(arange(1, d + 1)).T
        i = arange(0., self.N * 1.)
        inner = floor(2 ** k * x) * (2. ** (-k))
        return prod(sum(inner, axis=0) * (i + 1) + 1)


class Keane(Benchmark):

    """
    Keane objective function.

    This class defines the Keane global optimization problem. This
    is a multimodal minimization problem defined as follows:

    .. math::

        f_{\\text{Keane}}(\\mathbf{x}) = \\frac{\\sin^2(x_1 - x_2)\\sin^2(x_1 + x_2)}{\\sqrt{x_1^2 + x_2^2}}

    Here, :math:`n` represents the number of dimensions and :math:`x_i \\in [0, 10]` for :math:`i=1,2`.

    *Global optimum*: :math:`f(x_i) = 0.0` for :math:`\\mathbf{x} = [7.85396153, 7.85396135]`.

    """

    def __init__(self, dimensions=2):
        Benchmark.__init__(self, dimensions)

        self._bounds = zip([0.0] * self.N, [10.0] * self.N)

        self.global_optimum = [[7.85396153, 7.85396135]]
        self.custom_bounds = [(-1, 0.34), (-1, 0.34)]
        self.fglob = 0.

    def fun(self, x, *args):
        self.nfev += 1

        val = sin(x[0] - x[1]) ** 2 * sin(x[0] + x[1]) ** 2
        return val / sqrt(x[0] ** 2 + x[1] ** 2)


class Kowalik(Benchmark):

    """
    Kowalik objective function.

    This class defines the Kowalik global optimization problem. This
    is a multimodal minimization problem defined as follows:

    .. math::

       f_{\\text{Kowalik}}(\\mathbf{x}) = \\sum_{i=0}^{10} \\left [ a_i - \\frac{x_1(b_i^2+b_ix_2)}{b_i^2 + b_ix_3 + x_4} \\right ]^2

    Where:

    .. math::

       \\mathbf{a} = [4, 2, 1, 1/2, 1/4 1/8, 1/10, 1/12, 1/14, 1/16] \\\\
       \\mathbf{b} = [0.1957, 0.1947, 0.1735, 0.1600, 0.0844, 0.0627, 0.0456, 0.0342, 0.0323, 0.0235, 0.0246]

    Here, :math:`n` represents the number of dimensions and :math:`x_i \\in 
    [-5, 5]` for :math:`i=1,...,4`.

    *Global optimum*: :math:`f(x_i) = 0.00030748610` for :math:`\\mathbf{x} = 
    [0.192833, 0.190836, 0.123117, 0.135766]`.

    """
    # TODO, this is a NIST regression standard dataset

    def __init__(self, dimensions=4):
        Benchmark.__init__(self, dimensions)

        self._bounds = zip([-5.0] * self.N, [5.0] * self.N)
        self.global_optimum = [[0.192833, 0.190836, 0.123117, 0.135766]]
        self.fglob = 0.00030748610
        self.b = asarray([4.0, 2.0, 1.0, 1 / 2.0, 1 / 4.0, 1 / 6.0, 1 / 8.0,
                          1 / 10.0, 1 / 12.0, 1 / 14.0, 1 / 16.0])
        self.a = asarray([0.1957, 0.1947, 0.1735, 0.1600, 0.0844, 0.0627,
                          0.0456, 0.0342, 0.0323, 0.0235, 0.0246])

    def fun(self, x, *args):
        self.nfev += 1

        vec = self.a - (x[0] * (self.b ** 2 + self.b * x[1])
                   / (self.b ** 2 + self.b * x[2] + x[3]))
        return sum(vec ** 2)
