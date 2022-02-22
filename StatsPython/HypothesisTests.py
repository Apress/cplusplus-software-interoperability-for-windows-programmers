from Utilities import print_results, report_exception

import StatsPythonRaw as Stats

from scipy import stats


def hypothesis_test(t: float, p: float, alpha: float) -> None:
    """ Determine the outcome from the statistical test """

    if p<=alpha:
        print('Conclusion','p-value(=%f)'%p,'<=','alpha(=%.2f)'%alpha,'''We reject the null hypothesis H0. 
            We conclude that μ1 ≠ μ2 at %.2f level of significance.'''%alpha)
    else:
        print('Conclusion','p-value(=%f)'%p,'>','alpha(=%.2f)'%alpha,'''We do not reject the null hypothesis H0.
            We conclude that μ1 = μ2 at %.2f level of significance.'''%alpha)


def one_sample_ttest_scipy(data: list, mu: float) -> None:
    """ Perform a one-sample t-test using scipy """
    t_value, p_value = stats.ttest_1samp(data, mu)

    # Since alternative hypothesis is one tailed, We need to divide the p value by 2.
    one_tailed_p_value = float("{:.6f}".format(p_value/2))

    print('Test statistic is %f'%float("{:.6f}".format(t_value)))
    print('p-value for one tailed test is %f'%one_tailed_p_value)

    alpha = 0.05
    hypothesis_test(t_value, one_tailed_p_value, alpha)


def one_sample_ttest_statslib(data: list, mu: float) -> None:
    """ Perform a one-sample t-test using statslib """
    results = Stats.OneSampleTTest(mu, data)

    print_results(results, "One-sample t-test")

    p_value: float = results['pval']
    t_value: float = results['t']

    # Since alternative hypothesis is one tailed, We need to divide the p value by 2.
    one_tailed_p_value = float("{:.6f}".format(p_value/2))

    print('Test statistic is %f'%float("{:.6f}".format(t_value)))
    print('p-value for one tailed test is %f'%one_tailed_p_value)

    alpha = 0.05
    hypothesis_test(t_value, one_tailed_p_value, alpha)


def two_sample_ttest_scipy(x1: list, x2: list) -> None:
    """ Perform a two-sample t-test using scipy """
    t_value, p_value = stats.ttest_ind(x1, x2)

    print('Test statistic is %f'%float("{:.6f}".format(t_value)))
    print('p-value for two tailed test is %f'%p_value)

    alpha = 0.05
    hypothesis_test(t_value, p_value, alpha)


def two_sample_ttest_statslib(x1: list, x2: list) -> None:
    """ Perform a two-sample t-test using statslib """
    results = Stats.TwoSampleTTest(x1, x2)

    print_results(results, "Two-sample t-test")

    p_value: float = results['pval']
    t_value: float = results['t']

    print('Test statistic is %f'%float("{:.6f}".format(t_value)))
    print('p-value for two tailed test is %f'%p_value)

    alpha = 0.05
    hypothesis_test(t_value, p_value, alpha)


if __name__ == "__main__":
    """ Define standard data sets used elsewhere """

    # One-sample data
    mu: float = 165
    sys_bp: list = [183, 152, 178, 157, 194, 163, 144, 114, 178, 152, 118, 158, 172, 138]

    one_sample_ttest_scipy(sys_bp, mu)
    one_sample_ttest_statslib(sys_bp, mu)

    ammonium_chloride = [13.4,10.9,11.2,11.8,14,15.3,14.2,12.6,17,16.2,16.5,15.7]
    urea = [12,11.7,10.7,11.2,14.8,14.4,13.9,13.7,16.9,16,15.6,16]

    two_sample_ttest_scipy(ammonium_chloride, urea)
    two_sample_ttest_statslib(ammonium_chloride, urea) 
