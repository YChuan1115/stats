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
 * Sample from an inverse-gamma distribution
 */

namespace internal
{

template<typename T>
statslib_inline
T
rinvgamma_compute(T shape_par, T rate_par, rand_engine_t& engine)
{
    return( !invgamma_sanity_check(shape_par,rate_par) ? \
                STLIM<T>::quiet_NaN() :
            //
            T(1) / rgamma(shape_par,T(1)/rate_par,engine) );
}

template<typename T1, typename T2, typename TC = common_return_t<T1,T2>>
statslib_constexpr
TC
rinvgamma_type_check(const T1 shape_par, const T2 rate_par, rand_engine_t& engine)
noexcept
{
    return rinvgamma_compute(static_cast<TC>(shape_par),static_cast<TC>(rate_par),engine);
}

}

/**
 * @brief Random sampling function for the Inverse-Gamma distribution
 *
 * @param shape_par the shape parameter, a real-valued input.
 * @param rate_par the rate parameter, a real-valued input.
 * @param engine a random engine, passed by reference.
 *
 * @return a pseudo-random draw from the Inverse-Gamma distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rand_engine_t engine(1776);
 * stats::rinvgamma(3.0,2.0,engine);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rinvgamma(const T1 shape_par, const T2 rate_par, rand_engine_t& engine)
{
    return internal::rinvgamma_type_check(shape_par,rate_par,engine);
}

/**
 * @brief Random sampling function for the Inverse-Gamma distribution
 *
 * @param shape_par the shape parameter, a real-valued input.
 * @param rate_par the rate parameter, a real-valued input.
 * @param seed_val initialize the random engine with a non-negative integral-valued seed.
 *
 * @return a pseudo-random draw from the Inverse-Gamma distribution.
 *
 * Example:
 * \code{.cpp}
 * stats::rinvgamma(3.0,2.0,1776);
 * \endcode
 */

template<typename T1, typename T2>
statslib_inline
common_return_t<T1,T2>
rinvgamma(const T1 shape_par, const T2 rate_par, ullint_t seed_val)
{
    rand_engine_t engine(seed_val);
    return rinvgamma(shape_par,rate_par,engine);
}

//
// matrix/vector output

namespace internal
{

template<typename T>
statslib_inline
void
rinvgamma_vec(const T shape_par, const T rate_par, T* __stats_pointer_settings__ vals_out, const ullint_t num_elem)
{
    RAND_DIST_FN_VEC(rinvgamma,vals_out,num_elem,shape_par,rate_par);
}

}

#ifdef STATS_ENABLE_MATRIX_FEATURES
template<typename mT, typename eT>
statslib_inline
mT
rinvgamma(const ullint_t n, const ullint_t k, const eT shape_par, const eT rate_par)
{
    mT mat_out(n,k);

    internal::rinvgamma_vec<eT>(shape_par,rate_par,mat_ops::get_mem_ptr(mat_out),n*mat_ops::spacing(mat_out));

    return mat_out;
}
#endif
