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
 * Sample from a Binomial distribution
 */

//
// scalar ouput

/**
 * @brief Random sampling function for the Binomial distribution
 *
 * @param n_trials_par the number of trials, a positive integral-valued input.
 * @param prob_par the probability parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Beta distribution.
 * 
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rbinom(4,0.4,engine);
 * \endcode
 */

template<typename T>
statslib_inline
return_t<T>
rbinom(const llint_t n_trials_par, const T prob_par, rand_engine_t& engine)
{
    if (!internal::binom_sanity_check(n_trials_par,prob_par)) {
        return STLIM<T>::quiet_NaN();
    }

    //

    return_t<T> ret = return_t<T>(0);

    for (llint_t i=llint_t(0); i < n_trials_par; ++i)
    {
        ret += rbern(prob_par,engine);
    }

    return ret;
}

/**
 * @brief Random sampling function for the Binomial distribution
 *
 * @param n_trials_par the number of trials, a positive integral-valued input.
 * @param prob_par the probability parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Beta distribution.
 * 
 * Example:
 * \code{.cpp}
 * stats::rbinom(4,0.4,1776);
 * \endcode
 */

template<typename T>
statslib_inline
return_t<T>
rbinom(const llint_t n_trials_par, const T prob_par, ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rbinom(n_trials_par,prob_par,engine);
}

//
// matrix output

namespace internal
{

template<typename T>
statslib_inline
void
rbinom_vec(const llint_t n_trials_par, const T prob_par, T* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rbinom,vals_out,num_elem,n_trials_par,prob_par);
}

}

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename eT>
statslib_inline
mT
rbinom(const ullint_t n, const ullint_t k, const llint_t n_trials_par, const eT prob_par)
{
    mT mat_out(n,k);

    internal::rbinom_vec<eT>(n_trials_par,prob_par,mat_ops::get_mem_ptr(mat_out),n*mat_ops::spacing(mat_out));

    return mat_out;
}
#endif
