import numpy as np
import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from read_cifar import read_cifar, split_data


def test_read_cifar():
    data, labels = read_cifar("data")
    assert data.shape[0] == labels.shape[0]
    assert data.shape[1] == 3072
    assert labels.dtype == np.int64
    assert data.dtype == np.float32


def test_split_data():

    data = np.random.rand(100, 100)
    labels = np.random.rand(100, 100)

    train_length = 0.8 * data.shape[0]
    test_length = 0.2 * data.shape[0]

    train_data, train_labels, test_data, test_labels = split_data(data, labels, 0.8)

    assert train_data.shape[0] == train_length
    assert train_labels.shape[0] == train_length
    assert test_data.shape[0] == test_length
    assert test_labels.shape[0] == test_length
