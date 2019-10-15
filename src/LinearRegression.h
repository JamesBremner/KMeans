
/** Linear Regression
    @param[in] x indepedant variable values
    @param[in] y dependent variable values
    @return pair< intercept, slope >

    Usage:
    auto r = regression( x, y );
    y = r.first + r.second * x;
*/
std::pair<double,double> regression(
    const std::vector<double>& x,
    const std::vector<double>& y)
{
    const auto n    = x.size();
    const auto s_x  = std::accumulate(x.begin(), x.end(), 0.0);
    const auto s_y  = std::accumulate(y.begin(), y.end(), 0.0);
    const auto s_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
    const auto s_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    const auto slope = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
    const auto intercept = (s_y - slope * s_x) / x.size();
    return std::make_pair( intercept, slope );
}
