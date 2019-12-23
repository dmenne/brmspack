/*
    brmspack is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    brmspack is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with brmspack.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MODELS_HPP
#define MODELS_HPP
#define STAN__SERVICES__COMMAND_HPP
#include <rstan/rstaninc.hpp>
// Code generated by Stan version 2.19.1

#include <stan/model/model_header.hpp>

namespace model_inhaler_namespace {

using std::istream;
using std::string;
using std::stringstream;
using std::vector;
using stan::io::dump;
using stan::math::lgamma;
using stan::model::prob_grad;
using namespace stan::math;

static int current_statement_begin__;

stan::io::program_reader prog_reader__() {
    stan::io::program_reader reader;
    reader.add_event(0, 0, "start", "model_inhaler");
    reader.add_event(113, 111, "end", "model_inhaler");
    return reader;
}

template <typename T0__>
typename boost::math::tools::promote_args<T0__>::type
cloglog(const T0__& p, std::ostream* pstream__) {
    typedef typename boost::math::tools::promote_args<T0__>::type local_scalar_t__;
    typedef local_scalar_t__ fun_return_scalar_t__;
    const static bool propto__ = true;
    (void) propto__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

    int current_statement_begin__ = -1;
    try {

        current_statement_begin__ = 11;
        return stan::math::promote_scalar<fun_return_scalar_t__>(stan::math::log(-(stan::math::log((1 - p)))));
    } catch (const std::exception& e) {
        stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
        // Next line prevents compiler griping about no return
        throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
    }
}


struct cloglog_functor__ {
    template <typename T0__>
        typename boost::math::tools::promote_args<T0__>::type
    operator()(const T0__& p, std::ostream* pstream__) const {
        return cloglog(p, pstream__);
    }
};

template <bool propto, typename T1__, typename T2__, typename T3__>
typename boost::math::tools::promote_args<T1__, T2__, T3__>::type
sratio_cloglog_lpmf(const int& y,
                        const T1__& mu,
                        const Eigen::Matrix<T2__, Eigen::Dynamic, 1>& thres,
                        const T3__& disc, std::ostream* pstream__) {
    typedef typename boost::math::tools::promote_args<T1__, T2__, T3__>::type local_scalar_t__;
    typedef local_scalar_t__ fun_return_scalar_t__;
    const static bool propto__ = true;
    (void) propto__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

    int current_statement_begin__ = -1;
    try {
        {
        current_statement_begin__ = 23;
        int ncat(0);
        (void) ncat;  // dummy to suppress unused var warning
        stan::math::fill(ncat, std::numeric_limits<int>::min());
        stan::math::assign(ncat,(num_elements(thres) + 1));

        current_statement_begin__ = 24;
        validate_non_negative_index("p", "ncat", ncat);
        Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> p(ncat);
        stan::math::initialize(p, DUMMY_VAR__);
        stan::math::fill(p, DUMMY_VAR__);

        current_statement_begin__ = 25;
        validate_non_negative_index("q", "(ncat - 1)", (ncat - 1));
        Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> q((ncat - 1));
        stan::math::initialize(q, DUMMY_VAR__);
        stan::math::fill(q, DUMMY_VAR__);

        current_statement_begin__ = 26;
        int k(0);
        (void) k;  // dummy to suppress unused var warning
        stan::math::fill(k, std::numeric_limits<int>::min());
        stan::math::assign(k,1);


        current_statement_begin__ = 27;
        while (as_bool(logical_lte(k, std::min(y, (ncat - 1))))) {

            current_statement_begin__ = 28;
            stan::model::assign(q, 
                        stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                        (1 - inv_cloglog((disc * (get_base1(thres, k, "thres", 1) - mu)))), 
                        "assigning variable q");
            current_statement_begin__ = 29;
            stan::model::assign(p, 
                        stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                        (1 - get_base1(q, k, "q", 1)), 
                        "assigning variable p");
            current_statement_begin__ = 30;
            for (int kk = 1; kk <= (k - 1); ++kk) {
                current_statement_begin__ = 30;
                stan::model::assign(p, 
                            stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                            (get_base1(p, k, "p", 1) * get_base1(q, kk, "q", 1)), 
                            "assigning variable p");
            }
            current_statement_begin__ = 31;
            stan::math::assign(k, (k + 1));
        }
        current_statement_begin__ = 33;
        if (as_bool(logical_eq(y, ncat))) {

            current_statement_begin__ = 34;
            stan::model::assign(p, 
                        stan::model::cons_list(stan::model::index_uni(ncat), stan::model::nil_index_list()), 
                        prod(q), 
                        "assigning variable p");
        }
        current_statement_begin__ = 36;
        return stan::math::promote_scalar<fun_return_scalar_t__>(stan::math::log(get_base1(p, y, "p", 1)));
        }
    } catch (const std::exception& e) {
        stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
        // Next line prevents compiler griping about no return
        throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
    }
}
template <typename T1__, typename T2__, typename T3__>
typename boost::math::tools::promote_args<T1__, T2__, T3__>::type
sratio_cloglog_lpmf(const int& y,
                        const T1__& mu,
                        const Eigen::Matrix<T2__, Eigen::Dynamic, 1>& thres,
                        const T3__& disc, std::ostream* pstream__) {
    return sratio_cloglog_lpmf<false>(y,mu,thres,disc, pstream__);
}


struct sratio_cloglog_lpmf_functor__ {
    template <bool propto, typename T1__, typename T2__, typename T3__>
        typename boost::math::tools::promote_args<T1__, T2__, T3__>::type
    operator()(const int& y,
                        const T1__& mu,
                        const Eigen::Matrix<T2__, Eigen::Dynamic, 1>& thres,
                        const T3__& disc, std::ostream* pstream__) const {
        return sratio_cloglog_lpmf(y, mu, thres, disc, pstream__);
    }
};

template <bool propto, typename T1__, typename T2__, typename T3__, typename T4__>
typename boost::math::tools::promote_args<T1__, T2__, T3__, T4__>::type
sratio_cloglog_cs_lpmf(const int& y,
                           const T1__& mu,
                           const Eigen::Matrix<T2__, 1, Eigen::Dynamic>& mucs,
                           const Eigen::Matrix<T3__, Eigen::Dynamic, 1>& thres,
                           const T4__& disc, std::ostream* pstream__) {
    typedef typename boost::math::tools::promote_args<T1__, T2__, T3__, T4__>::type local_scalar_t__;
    typedef local_scalar_t__ fun_return_scalar_t__;
    const static bool propto__ = true;
    (void) propto__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

    int current_statement_begin__ = -1;
    try {
        {
        current_statement_begin__ = 50;
        int ncat(0);
        (void) ncat;  // dummy to suppress unused var warning
        stan::math::fill(ncat, std::numeric_limits<int>::min());
        stan::math::assign(ncat,(num_elements(thres) + 1));

        current_statement_begin__ = 51;
        validate_non_negative_index("p", "ncat", ncat);
        Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> p(ncat);
        stan::math::initialize(p, DUMMY_VAR__);
        stan::math::fill(p, DUMMY_VAR__);

        current_statement_begin__ = 52;
        validate_non_negative_index("q", "(ncat - 1)", (ncat - 1));
        Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> q((ncat - 1));
        stan::math::initialize(q, DUMMY_VAR__);
        stan::math::fill(q, DUMMY_VAR__);

        current_statement_begin__ = 53;
        int k(0);
        (void) k;  // dummy to suppress unused var warning
        stan::math::fill(k, std::numeric_limits<int>::min());
        stan::math::assign(k,1);


        current_statement_begin__ = 54;
        while (as_bool(logical_lte(k, std::min(y, (ncat - 1))))) {

            current_statement_begin__ = 55;
            stan::model::assign(q, 
                        stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                        (1 - inv_cloglog((disc * ((get_base1(thres, k, "thres", 1) - get_base1(mucs, k, "mucs", 1)) - mu)))), 
                        "assigning variable q");
            current_statement_begin__ = 56;
            stan::model::assign(p, 
                        stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                        (1 - get_base1(q, k, "q", 1)), 
                        "assigning variable p");
            current_statement_begin__ = 57;
            for (int kk = 1; kk <= (k - 1); ++kk) {
                current_statement_begin__ = 57;
                stan::model::assign(p, 
                            stan::model::cons_list(stan::model::index_uni(k), stan::model::nil_index_list()), 
                            (get_base1(p, k, "p", 1) * get_base1(q, kk, "q", 1)), 
                            "assigning variable p");
            }
            current_statement_begin__ = 58;
            stan::math::assign(k, (k + 1));
        }
        current_statement_begin__ = 60;
        if (as_bool(logical_eq(y, ncat))) {

            current_statement_begin__ = 61;
            stan::model::assign(p, 
                        stan::model::cons_list(stan::model::index_uni(ncat), stan::model::nil_index_list()), 
                        prod(q), 
                        "assigning variable p");
        }
        current_statement_begin__ = 63;
        return stan::math::promote_scalar<fun_return_scalar_t__>(stan::math::log(get_base1(p, y, "p", 1)));
        }
    } catch (const std::exception& e) {
        stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
        // Next line prevents compiler griping about no return
        throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
    }
}
template <typename T1__, typename T2__, typename T3__, typename T4__>
typename boost::math::tools::promote_args<T1__, T2__, T3__, T4__>::type
sratio_cloglog_cs_lpmf(const int& y,
                           const T1__& mu,
                           const Eigen::Matrix<T2__, 1, Eigen::Dynamic>& mucs,
                           const Eigen::Matrix<T3__, Eigen::Dynamic, 1>& thres,
                           const T4__& disc, std::ostream* pstream__) {
    return sratio_cloglog_cs_lpmf<false>(y,mu,mucs,thres,disc, pstream__);
}


struct sratio_cloglog_cs_lpmf_functor__ {
    template <bool propto, typename T1__, typename T2__, typename T3__, typename T4__>
        typename boost::math::tools::promote_args<T1__, T2__, T3__, T4__>::type
    operator()(const int& y,
                           const T1__& mu,
                           const Eigen::Matrix<T2__, 1, Eigen::Dynamic>& mucs,
                           const Eigen::Matrix<T3__, Eigen::Dynamic, 1>& thres,
                           const T4__& disc, std::ostream* pstream__) const {
        return sratio_cloglog_cs_lpmf(y, mu, mucs, thres, disc, pstream__);
    }
};

#include <meta_header.hpp>
 class model_inhaler : public prob_grad {
private:
        int N;
        std::vector<int> Y;
        int ncat;
        int K;
        matrix_d X;
        int Kcs;
        matrix_d Xcs;
        double disc;
        int prior_only;
        int Kc;
        matrix_d Xc;
        vector_d means_X;
public:
    model_inhaler(stan::io::var_context& context__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, 0, pstream__);
    }

    model_inhaler(stan::io::var_context& context__,
        unsigned int random_seed__,
        std::ostream* pstream__ = 0)
        : prob_grad(0) {
        ctor_body(context__, random_seed__, pstream__);
    }

    void ctor_body(stan::io::var_context& context__,
                   unsigned int random_seed__,
                   std::ostream* pstream__) {
        typedef double local_scalar_t__;

        boost::ecuyer1988 base_rng__ =
          stan::services::util::create_rng(random_seed__, 0);
        (void) base_rng__;  // suppress unused var warning

        current_statement_begin__ = -1;

        static const char* function__ = "model_inhaler_namespace::model_inhaler";
        (void) function__;  // dummy to suppress unused var warning
        size_t pos__;
        (void) pos__;  // dummy to suppress unused var warning
        std::vector<int> vals_i__;
        std::vector<double> vals_r__;
        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        try {
            // initialize data block variables from context__
            current_statement_begin__ = 67;
            context__.validate_dims("data initialization", "N", "int", context__.to_vec());
            N = int(0);
            vals_i__ = context__.vals_i("N");
            pos__ = 0;
            N = vals_i__[pos__++];
            check_greater_or_equal(function__, "N", N, 1);

            current_statement_begin__ = 68;
            validate_non_negative_index("Y", "N", N);
            context__.validate_dims("data initialization", "Y", "int", context__.to_vec(N));
            Y = std::vector<int>(N, int(0));
            vals_i__ = context__.vals_i("Y");
            pos__ = 0;
            size_t Y_k_0_max__ = N;
            for (size_t k_0__ = 0; k_0__ < Y_k_0_max__; ++k_0__) {
                Y[k_0__] = vals_i__[pos__++];
            }

            current_statement_begin__ = 69;
            context__.validate_dims("data initialization", "ncat", "int", context__.to_vec());
            ncat = int(0);
            vals_i__ = context__.vals_i("ncat");
            pos__ = 0;
            ncat = vals_i__[pos__++];
            check_greater_or_equal(function__, "ncat", ncat, 2);

            current_statement_begin__ = 70;
            context__.validate_dims("data initialization", "K", "int", context__.to_vec());
            K = int(0);
            vals_i__ = context__.vals_i("K");
            pos__ = 0;
            K = vals_i__[pos__++];
            check_greater_or_equal(function__, "K", K, 1);

            current_statement_begin__ = 71;
            validate_non_negative_index("X", "N", N);
            validate_non_negative_index("X", "K", K);
            context__.validate_dims("data initialization", "X", "matrix_d", context__.to_vec(N,K));
            X = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(N, K);
            vals_r__ = context__.vals_r("X");
            pos__ = 0;
            size_t X_j_2_max__ = K;
            size_t X_j_1_max__ = N;
            for (size_t j_2__ = 0; j_2__ < X_j_2_max__; ++j_2__) {
                for (size_t j_1__ = 0; j_1__ < X_j_1_max__; ++j_1__) {
                    X(j_1__, j_2__) = vals_r__[pos__++];
                }
            }

            current_statement_begin__ = 72;
            context__.validate_dims("data initialization", "Kcs", "int", context__.to_vec());
            Kcs = int(0);
            vals_i__ = context__.vals_i("Kcs");
            pos__ = 0;
            Kcs = vals_i__[pos__++];
            check_greater_or_equal(function__, "Kcs", Kcs, 1);

            current_statement_begin__ = 73;
            validate_non_negative_index("Xcs", "N", N);
            validate_non_negative_index("Xcs", "Kcs", Kcs);
            context__.validate_dims("data initialization", "Xcs", "matrix_d", context__.to_vec(N,Kcs));
            Xcs = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(N, Kcs);
            vals_r__ = context__.vals_r("Xcs");
            pos__ = 0;
            size_t Xcs_j_2_max__ = Kcs;
            size_t Xcs_j_1_max__ = N;
            for (size_t j_2__ = 0; j_2__ < Xcs_j_2_max__; ++j_2__) {
                for (size_t j_1__ = 0; j_1__ < Xcs_j_1_max__; ++j_1__) {
                    Xcs(j_1__, j_2__) = vals_r__[pos__++];
                }
            }

            current_statement_begin__ = 74;
            context__.validate_dims("data initialization", "disc", "double", context__.to_vec());
            disc = double(0);
            vals_r__ = context__.vals_r("disc");
            pos__ = 0;
            disc = vals_r__[pos__++];
            check_greater_or_equal(function__, "disc", disc, 0);

            current_statement_begin__ = 75;
            context__.validate_dims("data initialization", "prior_only", "int", context__.to_vec());
            prior_only = int(0);
            vals_i__ = context__.vals_i("prior_only");
            pos__ = 0;
            prior_only = vals_i__[pos__++];


            // initialize transformed data variables
            current_statement_begin__ = 78;
            Kc = int(0);
            stan::math::fill(Kc, std::numeric_limits<int>::min());
            stan::math::assign(Kc,(K - 1));

            current_statement_begin__ = 79;
            validate_non_negative_index("Xc", "N", N);
            validate_non_negative_index("Xc", "(K - 1)", (K - 1));
            Xc = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(N, (K - 1));
            stan::math::fill(Xc, DUMMY_VAR__);

            current_statement_begin__ = 80;
            validate_non_negative_index("means_X", "(K - 1)", (K - 1));
            means_X = Eigen::Matrix<double, Eigen::Dynamic, 1>((K - 1));
            stan::math::fill(means_X, DUMMY_VAR__);

            // execute transformed data statements
            current_statement_begin__ = 81;
            for (int i = 2; i <= K; ++i) {

                current_statement_begin__ = 82;
                stan::model::assign(means_X, 
                            stan::model::cons_list(stan::model::index_uni((i - 1)), stan::model::nil_index_list()), 
                            mean(stan::model::rvalue(X, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(i), stan::model::nil_index_list())), "X")), 
                            "assigning variable means_X");
                current_statement_begin__ = 83;
                stan::model::assign(Xc, 
                            stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni((i - 1)), stan::model::nil_index_list())), 
                            subtract(stan::model::rvalue(X, stan::model::cons_list(stan::model::index_omni(), stan::model::cons_list(stan::model::index_uni(i), stan::model::nil_index_list())), "X"), get_base1(means_X, (i - 1), "means_X", 1)), 
                            "assigning variable Xc");
            }

            // validate transformed data

            // validate, set parameter ranges
            num_params_r__ = 0U;
            param_ranges_i__.clear();
            current_statement_begin__ = 87;
            validate_non_negative_index("b", "Kc", Kc);
            num_params_r__ += Kc;
            current_statement_begin__ = 88;
            validate_non_negative_index("temp_Intercept", "(ncat - 1)", (ncat - 1));
            num_params_r__ += (ncat - 1);
            current_statement_begin__ = 89;
            validate_non_negative_index("bcs", "Kcs", Kcs);
            validate_non_negative_index("bcs", "(ncat - 1)", (ncat - 1));
            num_params_r__ += (Kcs * (ncat - 1));
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }

    ~model_inhaler() { }


    void transform_inits(const stan::io::var_context& context__,
                         std::vector<int>& params_i__,
                         std::vector<double>& params_r__,
                         std::ostream* pstream__) const {
        typedef double local_scalar_t__;
        stan::io::writer<double> writer__(params_r__, params_i__);
        size_t pos__;
        (void) pos__; // dummy call to supress warning
        std::vector<double> vals_r__;
        std::vector<int> vals_i__;

        current_statement_begin__ = 87;
        if (!(context__.contains_r("b")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable b missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("b");
        pos__ = 0U;
        validate_non_negative_index("b", "Kc", Kc);
        context__.validate_dims("parameter initialization", "b", "vector_d", context__.to_vec(Kc));
        Eigen::Matrix<double, Eigen::Dynamic, 1> b(Kc);
        size_t b_j_1_max__ = Kc;
        for (size_t j_1__ = 0; j_1__ < b_j_1_max__; ++j_1__) {
            b(j_1__) = vals_r__[pos__++];
        }
        try {
            writer__.vector_unconstrain(b);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable b: ") + e.what()), current_statement_begin__, prog_reader__());
        }

        current_statement_begin__ = 88;
        if (!(context__.contains_r("temp_Intercept")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable temp_Intercept missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("temp_Intercept");
        pos__ = 0U;
        validate_non_negative_index("temp_Intercept", "(ncat - 1)", (ncat - 1));
        context__.validate_dims("parameter initialization", "temp_Intercept", "vector_d", context__.to_vec((ncat - 1)));
        Eigen::Matrix<double, Eigen::Dynamic, 1> temp_Intercept((ncat - 1));
        size_t temp_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < temp_Intercept_j_1_max__; ++j_1__) {
            temp_Intercept(j_1__) = vals_r__[pos__++];
        }
        try {
            writer__.vector_unconstrain(temp_Intercept);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable temp_Intercept: ") + e.what()), current_statement_begin__, prog_reader__());
        }

        current_statement_begin__ = 89;
        if (!(context__.contains_r("bcs")))
            stan::lang::rethrow_located(std::runtime_error(std::string("Variable bcs missing")), current_statement_begin__, prog_reader__());
        vals_r__ = context__.vals_r("bcs");
        pos__ = 0U;
        validate_non_negative_index("bcs", "Kcs", Kcs);
        validate_non_negative_index("bcs", "(ncat - 1)", (ncat - 1));
        context__.validate_dims("parameter initialization", "bcs", "matrix_d", context__.to_vec(Kcs,(ncat - 1)));
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> bcs(Kcs, (ncat - 1));
        size_t bcs_j_2_max__ = (ncat - 1);
        size_t bcs_j_1_max__ = Kcs;
        for (size_t j_2__ = 0; j_2__ < bcs_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < bcs_j_1_max__; ++j_1__) {
                bcs(j_1__, j_2__) = vals_r__[pos__++];
            }
        }
        try {
            writer__.matrix_unconstrain(bcs);
        } catch (const std::exception& e) {
            stan::lang::rethrow_located(std::runtime_error(std::string("Error transforming variable bcs: ") + e.what()), current_statement_begin__, prog_reader__());
        }

        params_r__ = writer__.data_r();
        params_i__ = writer__.data_i();
    }

    void transform_inits(const stan::io::var_context& context,
                         Eigen::Matrix<double, Eigen::Dynamic, 1>& params_r,
                         std::ostream* pstream__) const {
      std::vector<double> params_r_vec;
      std::vector<int> params_i_vec;
      transform_inits(context, params_i_vec, params_r_vec, pstream__);
      params_r.resize(params_r_vec.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r(i) = params_r_vec[i];
    }


    template <bool propto__, bool jacobian__, typename T__>
    T__ log_prob(std::vector<T__>& params_r__,
                 std::vector<int>& params_i__,
                 std::ostream* pstream__ = 0) const {

        typedef T__ local_scalar_t__;

        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // dummy to suppress unused var warning

        T__ lp__(0.0);
        stan::math::accumulator<T__> lp_accum__;
        try {
            stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);

            // model parameters
            current_statement_begin__ = 87;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> b;
            (void) b;  // dummy to suppress unused var warning
            if (jacobian__)
                b = in__.vector_constrain(Kc, lp__);
            else
                b = in__.vector_constrain(Kc);

            current_statement_begin__ = 88;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> temp_Intercept;
            (void) temp_Intercept;  // dummy to suppress unused var warning
            if (jacobian__)
                temp_Intercept = in__.vector_constrain((ncat - 1), lp__);
            else
                temp_Intercept = in__.vector_constrain((ncat - 1));

            current_statement_begin__ = 89;
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, Eigen::Dynamic> bcs;
            (void) bcs;  // dummy to suppress unused var warning
            if (jacobian__)
                bcs = in__.matrix_constrain(Kcs, (ncat - 1), lp__);
            else
                bcs = in__.matrix_constrain(Kcs, (ncat - 1));

            // model body
            {
            current_statement_begin__ = 95;
            validate_non_negative_index("mucs", "N", N);
            validate_non_negative_index("mucs", "(ncat - 1)", (ncat - 1));
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, Eigen::Dynamic> mucs(N, (ncat - 1));
            stan::math::initialize(mucs, DUMMY_VAR__);
            stan::math::fill(mucs, DUMMY_VAR__);
            stan::math::assign(mucs,multiply(Xcs, bcs));

            current_statement_begin__ = 96;
            validate_non_negative_index("mu", "N", N);
            Eigen::Matrix<local_scalar_t__, Eigen::Dynamic, 1> mu(N);
            stan::math::initialize(mu, DUMMY_VAR__);
            stan::math::fill(mu, DUMMY_VAR__);
            stan::math::assign(mu,multiply(Xc, b));


            current_statement_begin__ = 98;
            lp_accum__.add(normal_log(b, 0, 5));
            current_statement_begin__ = 99;
            lp_accum__.add(student_t_log(temp_Intercept, 3, 0, 10));
            current_statement_begin__ = 100;
            lp_accum__.add(normal_log(to_vector(bcs), 0, 5));
            current_statement_begin__ = 102;
            if (as_bool(logical_negation(prior_only))) {

                current_statement_begin__ = 103;
                for (int n = 1; n <= N; ++n) {

                    current_statement_begin__ = 104;
                    lp_accum__.add(sratio_cloglog_cs_lpmf(get_base1(Y, n, "Y", 1), get_base1(mu, n, "mu", 1), get_base1(mucs, n, "mucs", 1), temp_Intercept, disc, pstream__));
                }
            }
            }

        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }

        lp_accum__.add(lp__);
        return lp_accum__.sum();

    } // log_prob()

    template <bool propto, bool jacobian, typename T_>
    T_ log_prob(Eigen::Matrix<T_,Eigen::Dynamic,1>& params_r,
               std::ostream* pstream = 0) const {
      std::vector<T_> vec_params_r;
      vec_params_r.reserve(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        vec_params_r.push_back(params_r(i));
      std::vector<int> vec_params_i;
      return log_prob<propto,jacobian,T_>(vec_params_r, vec_params_i, pstream);
    }


    void get_param_names(std::vector<std::string>& names__) const {
        names__.resize(0);
        names__.push_back("b");
        names__.push_back("temp_Intercept");
        names__.push_back("bcs");
        names__.push_back("b_Intercept");
    }


    void get_dims(std::vector<std::vector<size_t> >& dimss__) const {
        dimss__.resize(0);
        std::vector<size_t> dims__;
        dims__.resize(0);
        dims__.push_back(Kc);
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back((ncat - 1));
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back(Kcs);
        dims__.push_back((ncat - 1));
        dimss__.push_back(dims__);
        dims__.resize(0);
        dims__.push_back((ncat - 1));
        dimss__.push_back(dims__);
    }

    template <typename RNG>
    void write_array(RNG& base_rng__,
                     std::vector<double>& params_r__,
                     std::vector<int>& params_i__,
                     std::vector<double>& vars__,
                     bool include_tparams__ = true,
                     bool include_gqs__ = true,
                     std::ostream* pstream__ = 0) const {
        typedef double local_scalar_t__;

        vars__.resize(0);
        stan::io::reader<local_scalar_t__> in__(params_r__, params_i__);
        static const char* function__ = "model_inhaler_namespace::write_array";
        (void) function__;  // dummy to suppress unused var warning

        // read-transform, write parameters
        Eigen::Matrix<double, Eigen::Dynamic, 1> b = in__.vector_constrain(Kc);
        size_t b_j_1_max__ = Kc;
        for (size_t j_1__ = 0; j_1__ < b_j_1_max__; ++j_1__) {
            vars__.push_back(b(j_1__));
        }

        Eigen::Matrix<double, Eigen::Dynamic, 1> temp_Intercept = in__.vector_constrain((ncat - 1));
        size_t temp_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < temp_Intercept_j_1_max__; ++j_1__) {
            vars__.push_back(temp_Intercept(j_1__));
        }

        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> bcs = in__.matrix_constrain(Kcs, (ncat - 1));
        size_t bcs_j_2_max__ = (ncat - 1);
        size_t bcs_j_1_max__ = Kcs;
        for (size_t j_2__ = 0; j_2__ < bcs_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < bcs_j_1_max__; ++j_1__) {
                vars__.push_back(bcs(j_1__, j_2__));
            }
        }

        double lp__ = 0.0;
        (void) lp__;  // dummy to suppress unused var warning
        stan::math::accumulator<double> lp_accum__;

        local_scalar_t__ DUMMY_VAR__(std::numeric_limits<double>::quiet_NaN());
        (void) DUMMY_VAR__;  // suppress unused var warning

        if (!include_tparams__ && !include_gqs__) return;

        try {
            if (!include_gqs__ && !include_tparams__) return;
            if (!include_gqs__) return;
            // declare and define generated quantities
            current_statement_begin__ = 110;
            validate_non_negative_index("b_Intercept", "(ncat - 1)", (ncat - 1));
            Eigen::Matrix<double, Eigen::Dynamic, 1> b_Intercept((ncat - 1));
            stan::math::initialize(b_Intercept, DUMMY_VAR__);
            stan::math::fill(b_Intercept, DUMMY_VAR__);
            stan::math::assign(b_Intercept,add(temp_Intercept, dot_product(means_X, b)));

            // validate, write generated quantities
            current_statement_begin__ = 110;
            size_t b_Intercept_j_1_max__ = (ncat - 1);
            for (size_t j_1__ = 0; j_1__ < b_Intercept_j_1_max__; ++j_1__) {
                vars__.push_back(b_Intercept(j_1__));
            }

        } catch (const std::exception& e) {
            stan::lang::rethrow_located(e, current_statement_begin__, prog_reader__());
            // Next line prevents compiler griping about no return
            throw std::runtime_error("*** IF YOU SEE THIS, PLEASE REPORT A BUG ***");
        }
    }

    template <typename RNG>
    void write_array(RNG& base_rng,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& params_r,
                     Eigen::Matrix<double,Eigen::Dynamic,1>& vars,
                     bool include_tparams = true,
                     bool include_gqs = true,
                     std::ostream* pstream = 0) const {
      std::vector<double> params_r_vec(params_r.size());
      for (int i = 0; i < params_r.size(); ++i)
        params_r_vec[i] = params_r(i);
      std::vector<double> vars_vec;
      std::vector<int> params_i_vec;
      write_array(base_rng, params_r_vec, params_i_vec, vars_vec, include_tparams, include_gqs, pstream);
      vars.resize(vars_vec.size());
      for (int i = 0; i < vars.size(); ++i)
        vars(i) = vars_vec[i];
    }

    static std::string model_name() {
        return "model_inhaler";
    }


    void constrained_param_names(std::vector<std::string>& param_names__,
                                 bool include_tparams__ = true,
                                 bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t b_j_1_max__ = Kc;
        for (size_t j_1__ = 0; j_1__ < b_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "b" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t temp_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < temp_Intercept_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "temp_Intercept" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t bcs_j_2_max__ = (ncat - 1);
        size_t bcs_j_1_max__ = Kcs;
        for (size_t j_2__ = 0; j_2__ < bcs_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < bcs_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "bcs" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }

        if (!include_gqs__ && !include_tparams__) return;

        if (include_tparams__) {
        }

        if (!include_gqs__) return;
        size_t b_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < b_Intercept_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "b_Intercept" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
    }


    void unconstrained_param_names(std::vector<std::string>& param_names__,
                                   bool include_tparams__ = true,
                                   bool include_gqs__ = true) const {
        std::stringstream param_name_stream__;
        size_t b_j_1_max__ = Kc;
        for (size_t j_1__ = 0; j_1__ < b_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "b" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t temp_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < temp_Intercept_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "temp_Intercept" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
        size_t bcs_j_2_max__ = (ncat - 1);
        size_t bcs_j_1_max__ = Kcs;
        for (size_t j_2__ = 0; j_2__ < bcs_j_2_max__; ++j_2__) {
            for (size_t j_1__ = 0; j_1__ < bcs_j_1_max__; ++j_1__) {
                param_name_stream__.str(std::string());
                param_name_stream__ << "bcs" << '.' << j_1__ + 1 << '.' << j_2__ + 1;
                param_names__.push_back(param_name_stream__.str());
            }
        }

        if (!include_gqs__ && !include_tparams__) return;

        if (include_tparams__) {
        }

        if (!include_gqs__) return;
        size_t b_Intercept_j_1_max__ = (ncat - 1);
        for (size_t j_1__ = 0; j_1__ < b_Intercept_j_1_max__; ++j_1__) {
            param_name_stream__.str(std::string());
            param_name_stream__ << "b_Intercept" << '.' << j_1__ + 1;
            param_names__.push_back(param_name_stream__.str());
        }
    }

}; // model

}  // namespace

typedef model_inhaler_namespace::model_inhaler stan_model;


#endif
