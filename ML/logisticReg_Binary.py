import pandas
import numpy as np
import matplotlib.pyplot as plt


def sum(theta0, theta1, X, y, type):
    total = 0
    for i in range(0, y.size):
        hypothesis = theta0 + theta1 * X[i]
        exp = 1 + np.exp(-hypothesis)
        if type == 0:
            total += (y[i] - (1/exp))
        else:
            total += (y[i] - (1/exp))
    return total


def gradient_descent(X, y, theta0, theta1, alpha, num_iters):
    for i in range(0, num_iters):
        sum0 = sum(theta0, theta1, X, y, 0)
        sum1 = sum(theta0, theta1, X, y, 1)
        theta0 += alpha * sum0
        theta1 += alpha * sum1
    return theta0, theta1


def predict(X, y, theta0, theta1, alpha, num_iters):
    y_predict = []
    for i in range(0, y.size):
        yp = theta0 + theta1 * X[i]
        y_predict.append(yp)
    return y_predict


def main():
    data = pandas.read_csv('data.csv')
    pandas.plotting.scatter_matrix(data[['population', 'big']])

    X = data['population']
    y = data['big']

    m = y.size
    theta0 = 0
    theta1 = 0
    alpha = 0.01
    iterations = 1500

    theta0, theta1 = gradient_descent(X, y, theta0, theta1, alpha, iterations)
    print(theta0, theta1)
    y_predict = predict(X, y, theta0, theta1, alpha, iterations)

    total = 0
    for i in range(0, y.size):
        total = total + (y_predict[i] - y[i])
    error = total/m
    print(error)


if __name__ == "__main__":
    main()
