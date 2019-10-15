#include <numeric>

/** correlation coefficient.
    @param[in] X
    @param[in] Y
    @return correlation between X nd Y
*/
double correlationCoefficient(
    const std::vector<double>& X,
    const std::vector<double>& Y)
{
    double sum_X = 0, sum_Y = 0, sum_XY = 0;
    double squareSum_X = 0, squareSum_Y = 0;
    int n  = X.size();
    sum_X  = std::accumulate(X.begin(), X.end(), 0.0);
    sum_Y  = std::accumulate(Y.begin(), Y.end(), 0.0);
    sum_XY = std::inner_product(X.begin(), X.end(), Y.begin(), 0.0);
    squareSum_X = std::inner_product(X.begin(), X.end(), X.begin(), 0.0);
    squareSum_Y = std::inner_product(Y.begin(), Y.end(), Y.begin(), 0.0);

    double corr = (float)(n * sum_XY - sum_X * sum_Y)
                  / sqrt((n * squareSum_X - sum_X * sum_X)
                         * (n * squareSum_Y - sum_Y * sum_Y));

    return corr;
}
