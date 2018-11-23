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
 * Sample from a Beta distribution
 */

//
// scalar ouput

namespace internal
{

template<typename T>
statslib_inline
T
rbeta_compute(const T a_par, const T b_par, rand_engine_t& engine)
{
    if (!beta_sanity_check(a_par,b_par)) {
        return STLIM<T>::quiet_NaN();
    }

    //
    
    const T X = rgamma(a_par,T(1),engine);
    const T Y = rgamma(b_par,T(1),engine);
    
    return X / (X + Y);
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_inline
TC
rbeta_type_check(const T1 a_par, const T2 b_par, rand_engine_t& engine)
{
    return rbeta_compute(static_cast<TC>(a_par),static_cast<TC>(b_par),engine);
}

}

/**
 * @brief Random sampling function for the Beta distribution
 *
 * @param a_par a shape parameter, a real-valued input.
 * @param b_par a shape parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Beta distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rbeta(3.0,2.0,engine);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2> 
rbeta(const T1 a_par, const T2 b_par, rand_engine_t& engine)
{
    return internal::rbeta_type_check(a_par,b_par,engine);
}

/**
 * @brief Random sampling function for the Beta distribution
 *
 * @param a_par a shape parameter, a real-valued input.
 * @param b_par a shape parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Beta distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rbeta(3.0,2.0,1776);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2> 
rbeta(const T1 a_par, const T2 b_par, ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rbeta(a_par,b_par,engine);
}

//
// matrix/vector output

namespace internal
{

template<typename T>
statslib_inline
void
rbeta_vec(const T a_par, const T b_par, T* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rbeta,vals_out,num_elem,a_par,b_par);
}

}

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename eT>
statslib_inline
mT
rbeta(const ullint_t n, const ullint_t k, const eT a_par, const eT b_par)
{
    mT mat_out(n,k);

    internal::rbeta_vec<eT>(a_par,b_par,mat_ops::get_mem_ptr(mat_out),n*mat_ops::spacing(mat_out));

    return mat_out;
}
#endif
