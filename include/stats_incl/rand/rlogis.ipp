/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   Licensed under the Apache License, Version 2.0 (the "License");
  ##   you may not use this file except in compliance with the License.
  ##   You may obtain a copy of the License at
  ##
  ##       http://www.apache.org/licenses/LICENSE-2.0
  ##
  ##   Unless required by applicable law or agreed to in writing, software
  ##   distributed under the License is distributed on an "AS IS" BASIS,
  ##   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  ##   See the License for the specific language governing permissions and
  ##   limitations under the License.
  ##
  ################################################################################*/

/*
 * Sample from a logistic distribution
 */

//
// single draw

namespace internal
{

template<typename T>
statslib_inline
T
rlogis_compute(const T mu_par, const T sigma_par, rand_engine_t& engine)
{
    return( !logis_sanity_check(mu_par,sigma_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            qlogis(runif<T>(T(0),T(1),engine),mu_par,sigma_par) );
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_inline
TC
rlogis_type_check(const T1 mu_par, const T2 sigma_par, rand_engine_t& engine)
{
    return rlogis_compute(static_cast<TC>(mu_par),static_cast<TC>(sigma_par),engine);
}

}

/**
 * Random sampling function for the Logistic distribution
 *
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Logistic distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rlogis(1.0,2.0,engine);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rlogis(const T1 mu_par, const T2 sigma_par, rand_engine_t& engine)
{
    return internal::rlogis_type_check(mu_par,sigma_par,engine);
}

/**
 * Random sampling function for the Logistic distribution
 *
 * @param mu_par the location parameter, a real-valued input.
 * @param sigma_par the scale parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Logistic distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rlogis(1.0,2.0,1776);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rlogis(const T1 mu_par, const T2 sigma_par, ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rlogis(mu_par,sigma_par,engine);
}

//
// matrix/vector output

namespace internal
{

template<typename T>
statslib_inline
void
rlogis_vec(const T mu_par, const T sigma_par, T* vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rlogis,vals_out,num_elem,mu_par,sigma_par);
}

}

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename eT>
statslib_inline
mT
rlogis(const ullint_t n, const ullint_t k, const eT mu_par, const eT sigma_par)
{
    mT mat_out(n,k);

    internal::rlogis_vec<eT>(mu_par,sigma_par,mat_ops::get_mem_ptr(mat_out),n*mat_ops::spacing(mat_out));

    return mat_out;
}
#endif