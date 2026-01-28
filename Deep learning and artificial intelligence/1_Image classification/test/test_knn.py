import numpy as np
import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))
from knn import evaluate_knn, distance_matrix, knn_predict

# import pytest


def test_distance_matrix():
    matrix_A = np.array([[1, 2], [3, 4]])
    matrix_B = np.array([[5, 6], [7, 8]])

    expected_output = np.zeros((2, 2))
    for i in range(2):
        for j in range(2):
            expected_output[i, j] = np.sqrt(np.sum((matrix_A[i] - matrix_B[j]) ** 2))
    output = distance_matrix(matrix_A, matrix_B)
    np.testing.assert_almost_equal(output, expected_output, decimal=5)


def test_knn_predict():
    dists = np.array([[0, 10, 10], [10, 0, 0.8], [10, 0.8, 0]])
    labels_train = np.array([0, 1, 1])
    k = 2
    expected_output = np.array([0, 1, 1])
    output = knn_predict(dists, labels_train, k)
    np.testing.assert_array_equal(output, expected_output)


def test_evaluate_knn():
    data_train = np.array([[1, 2], [3, 4], [5, 6]])
    labels_train = np.array([0, 1, 1])
    data_test = np.array([[1, 2], [5, 6]])
    labels_test = np.array([0, 1])
    k = 2
    expected_accuracy = 1.0
    accuracy = evaluate_knn(data_train, labels_train, data_test, labels_test, k)
    assert accuracy == expected_accuracy
