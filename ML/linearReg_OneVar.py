import pandas
import matplotlib.pyplot as plt


def sum(theta0, theta1, X, y, type):
    total = 0
    for i in range(0, y.size):
        hypothesis = theta0 + theta1 * X[i]
        if type == 0:
            total += (hypothesis - y[i])
        else:
            total += (hypothesis - y[i])*X[i]
    return total


def gradient_descent(X, y, theta0, theta1, alpha, num_iters):
    for _ in range(0, num_iters):
        sum0 = sum(theta0, theta1, X, y, 0)
        sum1 = sum(theta0, theta1, X, y, 1)
        theta0 -= (alpha/y.size) * sum0
        theta1 -= (alpha/y.size) * sum1
    return theta0, theta1


def predict(X, y, theta0, theta1, alpha, num_iters):
    y_predict = []
    for i in range(0, y.size):
        yp = theta0 + theta1 * X[i]
        y_predict.append(yp)
    return y_predict


def main():
    data = pandas.read_csv('data.csv')
    pandas.plotting.scatter_matrix(data[['population', 'profit']])

    X = data['population']
    y = data['profit']

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
