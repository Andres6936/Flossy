#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <limits>

static_assert(std::numeric_limits<double>::is_iec559,
              "Double type is not IEEE 754 compliant.");
static_assert(std::numeric_limits<float>::is_iec559,
              "float_wrapper type is not IEEE 754 compliant.");

template <typename T>
class buffer {
  T* start;
  int length;

public:
  buffer(T* data, int len) noexcept
    : start(data)
    , length(len) {
    
    assert(len == 0 || (len > 0 && data != NULL));
  }

  T& operator[](int index) const noexcept {
    assert(0 <= index && index < length);
    return start[index];
  }
};

class diy_fp {
  static const uint64_t uint64_msb = 0x8000000000000000ULL;

public:
  static const int significand_size = 64;
  uint64_t f;
  int e;

  diy_fp() noexcept
    : f(0)
    , e(0) {}

  diy_fp(uint64_t significand, int exponent) noexcept
    : f(significand)
    , e(exponent) {}

  diy_fp& operator -=(const diy_fp& other) noexcept {
    assert(e == other.e);
    assert(f >= other.f);
    f -= other.f;
    return *this;
  }

  diy_fp& operator *=(const diy_fp& other) noexcept {
    const uint64_t max32 = std::numeric_limits<uint32_t>::max();
    uint64_t a = f >> 32;
    uint64_t b = f & max32;
    uint64_t c = other.f >> 32;
    uint64_t d = other.f & max32;
    uint64_t ac = a * c;
    uint64_t bc = b * c;
    uint64_t ad = a * d;
    uint64_t bd = b * d;
    uint64_t tmp = (bd >> 32) + (ad & max32) + (bc & max32) + (1U << 31);
    uint64_t result_f = ac + (ad >> 32) + (bc >> 32) + (tmp >> 32);
    e += other.e + 64;
    f = result_f;

    return *this;
  }

  void normalize() noexcept {
    assert(f != 0);
    uint64_t significand = f;
    int exponent = e;

    const uint64_t uint64_10msb = 0xFFC0000000000000ULL;
    while((significand & uint64_10msb) == 0) {
      significand <<= 10;
      exponent -= 10;
    }

    while((significand & uint64_msb) == 0) {
      significand <<= 1;
      exponent--;
    }

    f = significand;
    e = exponent;
  }

};

inline diy_fp normalize(const diy_fp& a) noexcept {
  diy_fp result = a;
  result.normalize();
  return result;
}

inline diy_fp operator*(const diy_fp& a, const diy_fp& b) noexcept {
  diy_fp result = a;
  result *= b;
  return result;
}

inline diy_fp operator-(const diy_fp& a, const diy_fp& b) noexcept {
  diy_fp result = a;
  result -= b;
  return result;
}

template <class Dest, class Source>
inline Dest bit_cast(const Source& source) noexcept {
  static_assert(sizeof(Dest) == sizeof(Source),
                "Dest and Source need to have the same size");

  Dest dest;
  memmove(&dest, &source, sizeof(dest));
  return dest;
}

/*
static const int kfast_dtoaMaximalLength = 17;
static const int kfast_dtoaMaximalSingleLength = 9;
*/

struct cached_power {
  uint64_t significand;
  int16_t binary_exponent;
  int16_t decimal_exponent;
};

static const cached_power cached_powers[] = {
  {0xfa8fd5a0081c0288ULL, -1220, -348}, {0xbaaee17fa23ebf76ULL, -1193, -340},
  {0x8b16fb203055ac76ULL, -1166, -332}, {0xcf42894a5dce35eaULL, -1140, -324},
  {0x9a6bb0aa55653b2dULL, -1113, -316}, {0xe61acf033d1a45dfULL, -1087, -308},
  {0xab70fe17c79ac6caULL, -1060, -300}, {0xff77b1fcbebcdc4fULL, -1034, -292},
  {0xbe5691ef416bd60cULL, -1007, -284}, {0x8dd01fad907ffc3cULL,  -980, -276},
  {0xd3515c2831559a83ULL,  -954, -268}, {0x9d71ac8fada6c9b5ULL,  -927, -260},
  {0xea9c227723ee8bcbULL,  -901, -252}, {0xaecc49914078536dULL,  -874, -244},
  {0x823c12795db6ce57ULL,  -847, -236}, {0xc21094364dfb5637ULL,  -821, -228},
  {0x9096ea6f3848984fULL,  -794, -220}, {0xd77485cb25823ac7ULL,  -768, -212},
  {0xa086cfcd97bf97f4ULL,  -741, -204}, {0xef340a98172aace5ULL,  -715, -196},
  {0xb23867fb2a35b28eULL,  -688, -188}, {0x84c8d4dfd2c63f3bULL,  -661, -180},
  {0xc5dd44271ad3cdbaULL,  -635, -172}, {0x936b9fcebb25c996ULL,  -608, -164},
  {0xdbac6c247d62a584ULL,  -582, -156}, {0xa3ab66580d5fdaf6ULL,  -555, -148},
  {0xf3e2f893dec3f126ULL,  -529, -140}, {0xb5b5ada8aaff80b8ULL,  -502, -132},
  {0x87625f056c7c4a8bULL,  -475, -124}, {0xc9bcff6034c13053ULL,  -449, -116},
  {0x964e858c91ba2655ULL,  -422, -108}, {0xdff9772470297ebdULL,  -396, -100},
  {0xa6dfbd9fb8e5b88fULL,  -369,  -92}, {0xf8a95fcf88747d94ULL,  -343,  -84},
  {0xb94470938fa89bcfULL,  -316,  -76}, {0x8a08f0f8bf0f156bULL,  -289,  -68},
  {0xcdb02555653131b6ULL,  -263,  -60}, {0x993fe2c6d07b7facULL,  -236,  -52},
  {0xe45c10c42a2b3b06ULL,  -210,  -44}, {0xaa242499697392d3ULL,  -183,  -36},
  {0xfd87b5f28300ca0eULL,  -157,  -28}, {0xbce5086492111aebULL,  -130,  -20},
  {0x8cbccc096f5088ccULL,  -103,  -12}, {0xd1b71758e219652cULL,   -77,   -4},
  {0x9c40000000000000ULL,   -50,    4}, {0xe8d4a51000000000ULL,   -24,   12},
  {0xad78ebc5ac620000ULL,     3,   20}, {0x813f3978f8940984ULL,    30,   28},
  {0xc097ce7bc90715b3ULL,    56,   36}, {0x8f7e32ce7bea5c70ULL,    83,   44},
  {0xd5d238a4abe98068ULL,   109,   52}, {0x9f4f2726179a2245ULL,   136,   60},
  {0xed63a231d4c4fb27ULL,   162,   68}, {0xb0de65388cc8ada8ULL,   189,   76},
  {0x83c7088e1aab65dbULL,   216,   84}, {0xc45d1df942711d9aULL,   242,   92},
  {0x924d692ca61be758ULL,   269,  100}, {0xda01ee641a708deaULL,   295,  108},
  {0xa26da3999aef774aULL,   322,  116}, {0xf209787bb47d6b85ULL,   348,  124},
  {0xb454e4a179dd1877ULL,   375,  132}, {0x865b86925b9bc5c2ULL,   402,  140},
  {0xc83553c5c8965d3dULL,   428,  148}, {0x952ab45cfa97a0b3ULL,   455,  156},
  {0xde469fbd99a05fe3ULL,   481,  164}, {0xa59bc234db398c25ULL,   508,  172},
  {0xf6c69a72a3989f5cULL,   534,  180}, {0xb7dcbf5354e9beceULL,   561,  188},
  {0x88fcf317f22241e2ULL,   588,  196}, {0xcc20ce9bd35c78a5ULL,   614,  204},
  {0x98165af37b2153dfULL,   641,  212}, {0xe2a0b5dc971f303aULL,   667,  220},
  {0xa8d9d1535ce3b396ULL,   694,  228}, {0xfb9b7cd9a4a7443cULL,   720,  236},
  {0xbb764c4ca7a44410ULL,   747,  244}, {0x8bab8eefb6409c1aULL,   774,  252},
  {0xd01fef10a657842cULL,   800,  260}, {0x9b10a4e5e9913129ULL,   827,  268},
  {0xe7109bfba19c0c9dULL,   853,  276}, {0xac2820d9623bf429ULL,   880,  284},
  {0x80444b5e7aa7cf85ULL,   907,  292}, {0xbf21e44003acdd2dULL,   933,  300},
  {0x8e679c2f5e44ff8fULL,   960,  308}, {0xd433179d9c8cb841ULL,   986,  316},
  {0x9e19db92b4e31ba9ULL,  1013,  324}, {0xeb96bf6ebadf77d9ULL,  1039,  332},
  {0xaf87023b9bf0ee6bULL,  1066,  340}
};

static const int decimal_exponent_distance = 8;
static const double d_1_log2_10 = 0.30102999566398114;
static const int cached_powers_offset = 348;


inline void power_for_bin_exp_range(int min_exponent, int max_exponent,
                                    diy_fp* power, int* decimal_exponent) noexcept {

  double k     = ceil((min_exponent + diy_fp::significand_size - 1) * d_1_log2_10);
  int    index = (cached_powers_offset + int(k) - 1) / decimal_exponent_distance + 1;

  assert(0 <= index && index < int(sizeof(cached_powers) / sizeof(cached_powers[0])));

  cached_power cpower = cached_powers[index];

  (void) max_exponent;
  assert(min_exponent <= cpower.binary_exponent);
  assert(cpower.binary_exponent <= max_exponent);

  *decimal_exponent = cpower.decimal_exponent;
  *power = diy_fp(cpower.significand, cpower.binary_exponent);
}


struct double_traits {
  static const uint64_t sign_mask                 = 0x8000000000000000ULL;
  static const uint64_t exponent_mask             = 0x7FF0000000000000ULL;
  static const uint64_t significand_mask          = 0x000FFFFFFFFFFFFFULL;
  static const uint64_t hidden_bit                = 0x0010000000000000ULL;
  static const int      physical_significand_size = 52;
  static const int      significand_size          = 53;
  static const int      exponent_bias             = 0x3FF + physical_significand_size;
  static const int      denormal_exponent         = -exponent_bias + 1;
  static const int      max_exponent              = 0x7FF - exponent_bias;
  static const uint64_t infinity                  = 0x7FF0000000000000ULL;
  static const uint64_t nan                       = 0x7FF8000000000000ULL;

  typedef double        float_type;
  typedef uint64_t      uint_type;
};

struct single_traits {
  static const uint32_t sign_mask                 = 0x80000000;
  static const uint32_t exponent_mask             = 0x7F800000;
  static const uint32_t significand_mask          = 0x007FFFFF;
  static const uint32_t hidden_bit                = 0x00800000;
  static const int      physical_significand_size = 23;
  static const int      significand_size          = 24;
  static const int      exponent_bias             = 0x7F + physical_significand_size;
  static const int      denormal_exponent         = -exponent_bias + 1;
  static const int      max_exponent              = 0xFF - exponent_bias;
  static const uint32_t infinity                  = 0x7F800000;
  static const uint32_t nan                       = 0x7FC00000;

  typedef float         float_type;
  typedef uint32_t      uint_type;
};

template<typename Traits>
class float_wrapper {
 public:

  typedef typename Traits::float_type float_type;
  typedef typename Traits::uint_type uint_type;

  static_assert(sizeof(float_type) == sizeof(uint_type),
                "float_wrapper and int type size mismatch in trait class");

  explicit float_wrapper(float_type d) noexcept
    : data(bit_cast<uint_type>(d)) {}

  diy_fp as_diy_fp() const noexcept {
    assert(sign() > 0);
    assert(!is_special());
    return diy_fp(significand(), exponent());
  }

  diy_fp as_normalized_diy_fp() const noexcept {
    assert(value() > 0.0);
    uint_type f = significand();
    int e = exponent();

    while((f & Traits::hidden_bit) == 0) {
      f <<= 1;
      e--;
    }
    f <<= diy_fp::significand_size - Traits::significand_size;
    e -= diy_fp::significand_size - Traits::significand_size;
    return diy_fp(f, e);
  }

  int exponent() const noexcept {
    if (is_denormal()) return Traits::denormal_exponent;

    int biased_e = int((data & Traits::exponent_mask)
                        >> Traits::physical_significand_size);
    return biased_e - Traits::exponent_bias;
  }

  uint_type significand() const noexcept {
    uint_type significand = data & Traits::significand_mask;

    if (!is_denormal()) {
      return significand + Traits::hidden_bit;
    } else {
      return significand;
    }
  }

  bool is_denormal() const noexcept {
    return (data & Traits::exponent_mask) == 0;
  }

  bool is_special() const noexcept {
    return (data & Traits::exponent_mask) == Traits::exponent_mask;
  }

  int sign() const noexcept {
    return (data & Traits::sign_mask) == 0? 1: -1;
  }

  void normalized_boundaries(diy_fp* out_m_minus, diy_fp* out_m_plus) const noexcept {
    assert(value() > 0.0);
    diy_fp v = as_diy_fp();
    diy_fp m_plus = normalize(diy_fp((v.f << 1) + 1, v.e - 1));
    diy_fp m_minus;

    if(lower_boundary_is_closer()) {
      m_minus = diy_fp((v.f << 2) - 1, v.e - 2);
    } else {
      m_minus = diy_fp((v.f << 1) - 1, v.e - 1);
    }

    m_minus.f = m_minus.f << (m_minus.e - m_plus.e);
    m_minus.e = m_plus.e;
    *out_m_plus = m_plus;
    *out_m_minus = m_minus;
  }

  bool lower_boundary_is_closer() const noexcept {
    bool physical_significand_is_zero = ((data & Traits::significand_mask) == 0);
    return physical_significand_is_zero
           && (exponent() != Traits::denormal_exponent);
  }

  float_type value() const { return bit_cast<float_type>(data); }

 private:

  const uint_type data;

  float_wrapper() = delete;
  float_wrapper(float_wrapper const&) = delete;
  float_wrapper& operator=(float_wrapper const&) = delete;
  float_wrapper(float_wrapper&&) = delete;
  float_wrapper& operator=(float_wrapper&&) = delete;
};

typedef float_wrapper<double_traits> Double;
typedef float_wrapper<single_traits> Single;


static const int minimal_target_exponent = -60;
static const int maximal_target_exponent = -32;

inline bool round_weed(buffer<char> buffer, int length,
                       uint64_t distance_too_high_w,
                       uint64_t unsafe_interval, uint64_t rest,
                       uint64_t ten_kappa, uint64_t unit) noexcept {

  uint64_t small_distance = distance_too_high_w - unit;
  uint64_t big_distance = distance_too_high_w + unit;

  assert(rest <= unsafe_interval);

  while(rest < small_distance && unsafe_interval - rest >= ten_kappa &&
          (rest + ten_kappa < small_distance ||
            small_distance - rest >= rest + ten_kappa - small_distance)) {
    buffer[length - 1]--;
    rest += ten_kappa;
  }

  if(rest < big_distance &&
      unsafe_interval - rest >= ten_kappa &&
      (rest + ten_kappa < big_distance ||
       big_distance - rest > rest + ten_kappa - big_distance)) {
    return false;
  }
  return (2 * unit <= rest) && (rest <= unsafe_interval - 4 * unit);
}


inline bool round_weed_counted(buffer<char> buffer, int length, uint64_t rest,
                               uint64_t ten_kappa, uint64_t unit,
                               int* kappa) noexcept {
  assert(rest < ten_kappa);

  if(unit >= ten_kappa) {
    return false;
  }

  if(ten_kappa - unit <= unit) {
    return false;
  }

  if((ten_kappa - rest > rest) && (ten_kappa - 2 * rest >= 2 * unit)) {
    return true;
  }

  if((rest > unit) && (ten_kappa - (rest - unit) <= (rest - unit))) {
    buffer[length - 1]++;
    for(int i = length - 1; i > 0; --i) {
      if (buffer[i] != '0' + 10) break;
      buffer[i] = '0';
      buffer[i - 1]++;
    }

    if (buffer[0] == '0' + 10) {
      buffer[0] = '1';
      (*kappa) += 1;
    }
    return true;
  }
  return false;
}


static unsigned int const small_powers_of_ten[] = {
  0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000
};


inline void biggest_power_ten(uint32_t number, int number_bits,
                              uint32_t* power, int* exponent_plus_one) noexcept {

  assert(number < (1u << (number_bits + 1)));
  int exponent_plus_one_guess = ((number_bits + 1) * 1233 >> 12) + 1;

  if(number < small_powers_of_ten[exponent_plus_one_guess]) {
    exponent_plus_one_guess--;
  }

  *power = small_powers_of_ten[exponent_plus_one_guess];
  *exponent_plus_one = exponent_plus_one_guess;
}


inline bool digit_gen(diy_fp low, diy_fp w, diy_fp high, buffer<char> buffer,
                      int* length, int* kappa) noexcept {

  assert(low.e == w.e && w.e == high.e);
  assert(low.f + 1 <= high.f - 1);
  assert(minimal_target_exponent <= w.e && w.e <= maximal_target_exponent);

  uint64_t unit = 1;
  diy_fp too_low = diy_fp(low.f - unit, low.e);
  diy_fp too_high = diy_fp(high.f + unit, high.e);
  diy_fp unsafe_interval = too_high - too_low;
  diy_fp one = diy_fp(1ULL << -w.e, w.e);
  uint32_t integrals = uint32_t(too_high.f >> -one.e);
  uint64_t fractionals = too_high.f & (one.f - 1ULL);
  uint32_t divisor;
  int divisor_exponent_plus_one;

  biggest_power_ten(integrals, diy_fp::significand_size - (-one.e), &divisor,
                    &divisor_exponent_plus_one);

  *kappa = divisor_exponent_plus_one;
  *length = 0;

  while(*kappa > 0) {
    int digit = integrals / divisor;
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    integrals %= divisor;
    (*kappa)--;
    uint64_t rest = (uint64_t(integrals) << -one.e) + fractionals;

    if(rest < unsafe_interval.f) {
      return round_weed(buffer, *length, (too_high - w).f, unsafe_interval.f,
                        rest, uint64_t(divisor) << -one.e, unit);
    }

    divisor /= 10;
  }

  assert(one.e >= -60);
  assert(fractionals < one.f);
  assert(0xFFFFFFFFFFFFFFFFULL / 10 >= one.f);

  for(;;) {
    fractionals *= 10;
    unit *= 10;
    unsafe_interval.f = unsafe_interval.f * 10;
    int digit = int(fractionals >> -one.e);
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    fractionals &= one.f - 1;
    (*kappa)--;

    if(fractionals < unsafe_interval.f) {
      return round_weed(buffer, *length, (too_high - w).f * unit,
                        unsafe_interval.f, fractionals, one.f, unit);
    }
  }
}

inline bool digit_gen_counted(diy_fp w, int requested_digits, buffer<char> buffer,
                              int* length, int* kappa) noexcept {

  assert(minimal_target_exponent <= w.e && w.e <= maximal_target_exponent);

  uint64_t w_error = 1;
  diy_fp one = diy_fp(1ULL << -w.e, w.e);
  uint32_t integrals = uint32_t(w.f >> -one.e);
  uint64_t fractionals = w.f & (one.f - 1);
  uint32_t divisor;
  int divisor_exponent_plus_one;

  biggest_power_ten(integrals, diy_fp::significand_size - (-one.e), &divisor,
                    &divisor_exponent_plus_one);
  *kappa = divisor_exponent_plus_one;
  *length = 0;

  while(*kappa > 0) {
    int digit = integrals / divisor;
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    requested_digits--;
    integrals %= divisor;
    (*kappa)--;

    if(requested_digits == 0) {
      break;
    }
    divisor /= 10;
  }

  if(requested_digits == 0) {
    uint64_t rest = (uint64_t(integrals) << -one.e) + fractionals;
    return round_weed_counted(buffer, *length, rest, uint64_t(divisor) << -one.e,
                              w_error, kappa);
  }

  assert(one.e >= -60);
  assert(fractionals < one.f);
  assert(0xFFFFFFFFFFFFFFFFULL / 10 >= one.f);

  while(requested_digits > 0 && fractionals > w_error) {
    fractionals *= 10;
    w_error *= 10;
    int digit = int(fractionals >> -one.e);
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    requested_digits--;
    fractionals &= one.f - 1;
    (*kappa)--;
  }

  if(requested_digits != 0) {
    return false;
  }

  return round_weed_counted(buffer, *length, fractionals, one.f, w_error, kappa);
}


enum class fast_dtoa_mode {
  shortest,
  shortest_single,
  precision
};

inline bool grisu3(double v, fast_dtoa_mode mode, buffer<char> buffer,
                   int* length, int* decimal_exponent) noexcept {

  diy_fp w = Double(v).as_normalized_diy_fp();
  diy_fp boundary_minus, boundary_plus;

  if(mode == fast_dtoa_mode::shortest) {
    Double(v).normalized_boundaries(&boundary_minus, &boundary_plus);
  } else {
    assert(mode == fast_dtoa_mode::shortest_single);
    float single_v = float(v);
    Single(single_v).normalized_boundaries(&boundary_minus, &boundary_plus);
  }
  assert(boundary_plus.e == w.e);

  int ten_mk_minimal_binary_exponent = minimal_target_exponent 
      - (w.e + diy_fp::significand_size);
  int ten_mk_maximal_binary_exponent = maximal_target_exponent
      - (w.e + diy_fp::significand_size);

  diy_fp ten_mk;
  int mk;
  power_for_bin_exp_range(ten_mk_minimal_binary_exponent,
                          ten_mk_maximal_binary_exponent, &ten_mk, &mk);

  assert((minimal_target_exponent <= w.e + ten_mk.e + diy_fp::significand_size)
      && (maximal_target_exponent >= w.e + ten_mk.e + diy_fp::significand_size));

  diy_fp scaled_w = w * ten_mk;
  assert(scaled_w.e == boundary_plus.e + ten_mk.e + diy_fp::significand_size);

  diy_fp scaled_boundary_minus = boundary_minus * ten_mk;
  diy_fp scaled_boundary_plus  = boundary_plus  * ten_mk;

  int kappa;
  bool result = digit_gen(scaled_boundary_minus, scaled_w, scaled_boundary_plus,
                          buffer, length, &kappa);
  *decimal_exponent = -mk + kappa;
  return result;
}


inline bool grisu3_counted(double v, int requested_digits, buffer<char> buffer,
                           int* length, int* decimal_exponent) noexcept {

  diy_fp w = Double(v).as_normalized_diy_fp();

  int ten_mk_minimal_binary_exponent = minimal_target_exponent 
      - (w.e + diy_fp::significand_size);
  int ten_mk_maximal_binary_exponent = maximal_target_exponent
      - (w.e + diy_fp::significand_size);

  diy_fp ten_mk;
  int mk;
  power_for_bin_exp_range(ten_mk_minimal_binary_exponent,
                          ten_mk_maximal_binary_exponent, &ten_mk, &mk);

  assert((minimal_target_exponent <= w.e + ten_mk.e + diy_fp::significand_size)
      && (maximal_target_exponent >= w.e + ten_mk.e + diy_fp::significand_size));

  diy_fp scaled_w = w * ten_mk;

  int kappa;
  bool result = digit_gen_counted(scaled_w, requested_digits, buffer, length, &kappa);
  *decimal_exponent = -mk + kappa;
  return result;
}


inline bool fast_dtoa(double v, fast_dtoa_mode mode, int requested_digits,
                      buffer<char> buffer, int* length, int* decimal_point) noexcept {
  assert(v > 0);
  assert(!Double(v).is_special());

  bool result = false;
  int decimal_exponent = 0;

  switch(mode) {
  case fast_dtoa_mode::shortest:
  case fast_dtoa_mode::shortest_single:
    result = grisu3(v, mode, buffer, length, &decimal_exponent);
    break;
  case fast_dtoa_mode::precision:
    result = grisu3_counted(v, requested_digits, buffer, length, &decimal_exponent);
    break;
  default:
    abort();
  }

  if(result) {
    *decimal_point = *length + decimal_exponent;
    buffer[*length] = '\0';
  }
  return result;
}
