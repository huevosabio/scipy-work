# -*- coding: utf-8 -*-
from __future__ import division, print_function, absolute_import
import numpy as np
from numpy import (abs, arctan2, asarray, cos, exp, floor, log, log10,
                   arange, pi, prod, roll, sign, sin, sqrt, sum, where,
                   zeros, tan, tanh, dot)

from scipy.misc import factorial
from .go_benchmark import Benchmark


class Infinity(Benchmark):

    """
    Infinity objective function.

    This class defines the Infinity global optimization problem. This
    is a multimodal minimization problem defined as follows:

    .. math::

        f_{\\text{Infinity}}(\\mathbf{x}) = \\sum_{i=1}^{n} x_i^{6} \\left [ \\sin\\left ( \\frac{1}{x_i} \\right )+2 \\right ]

    Here, :math:`n` represents the number of dimensions and :math:`x_i \\in [-1, 1]` for :math:`i=1,...,n`.

    *Global optimum*: :math:`f(x_i) = 0` for :math:`x_i = 0` for :math:`i=1,...,n`

    """

    def __init__(self, dimensions=2):
        Benchmark.__init__(self, dimensions)

        self._bounds = zip([-1.0] * self.N, [1.0] * self.N)

        self.global_optimum = [[1e-16 for _ in range(self.N)]]
        self.fglob = 0.0
        self.change_dimensionality = True

    def fun(self, x, *args):
        self.nfev += 1

        return sum(x ** 6.0 * (sin(1.0 / x) + 2.0))