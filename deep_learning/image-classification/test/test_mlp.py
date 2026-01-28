import numpy as np
import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from mlp import learn_once_cross_entropy, one_hot, softmax


def test_one_hot():
    labels = np.array([0, 1, 2, 1, 0])
    one_hot_encoded = one_hot(labels)
    expected_output = np.array([[1, 0, 0], [0, 1, 0], [0, 0, 1], [0, 1, 0], [1, 0, 0]])
    assert np.array_equal(one_hot_encoded, expected_output)


def test_softmax():
    x = np.array([[1, 2, 3], [1, 2, 3]])
    softmax_output = softmax(x)
    expected_output = np.array(
        [[0.09003057, 0.24472847, 0.66524096], [0.09003057, 0.24472847, 0.66524096]]
    )
    assert np.allclose(softmax_output, expected_output, atol=1e-6)


def test_learn_once_cross_entropy():
    w1 = np.random.rand(3, 2)
    b1 = np.random.rand(1, 2)
    w2 = np.random.rand(2, 2)
    b2 = np.random.rand(1, 2)
    data = np.random.rand(5, 3)
    targets = np.array([0, 1, 0, 1, 0])
    learning_rate = 0.01

    w1_new, b1_new, w2_new, b2_new, loss = learn_once_cross_entropy(
        w1=w1,
        b1=b1,
        w2=w2,
        b2=b2,
        data=data,
        targets=targets,
        learning_rate=learning_rate,
    )

    assert w1_new.shape == w1.shape
    assert b1_new.shape == b1.shape
    assert w2_new.shape == w2.shape
    assert b2_new.shape == b2.shape
    assert isinstance(loss, float)
    assert loss > 0
