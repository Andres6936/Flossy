#include <cstdlib>
#include <cstring>
#include <assert.h>
#include <cstdint>
#include <stdarg.h>
#include <cmath>
#include <limits>

static_assert(std::numeric_limits<double>::is_iec559, "Double type is not IEEE 754 compliant.");
static_assert(std::numeric_limits<float>::is_iec559, "Float type is not IEEE 754 compliant.");

[[noreturn]] inline void unreachable() {
  abort();
}

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)                                   \
  ((sizeof(a) / sizeof(*(a))) /                         \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
#endif


template <typename T>
class Vector {
  T* start;
  int length;

public:
  Vector(T* data, int len)
    : start(data)
    , length(len) {
    
    assert(len == 0 || (len > 0 && data != NULL));
  }

  T& operator[](int index) const {
    assert(0 <= index && index < length);
    return start[index];
  }
};

class DiyFp {
 public:
  static const int kSignificandSize = 64;

  DiyFp() : f_(0), e_(0) {}
  DiyFp(uint64_t significand, int exponent) : f_(significand), e_(exponent) {}

  void Subtract(const DiyFp& other) {
    assert(e_ == other.e_);
    assert(f_ >= other.f_);
    f_ -= other.f_;
  }

  static DiyFp Minus(const DiyFp& a, const DiyFp& b) {
    DiyFp result = a;
    result.Subtract(b);
    return result;
  }


  void Multiply(const DiyFp& other) {
    const uint64_t kM32 = 0xFFFFFFFFU;
    uint64_t a = f_ >> 32;
    uint64_t b = f_ & kM32;
    uint64_t c = other.f_ >> 32;
    uint64_t d = other.f_ & kM32;
    uint64_t ac = a * c;
    uint64_t bc = b * c;
    uint64_t ad = a * d;
    uint64_t bd = b * d;
    uint64_t tmp = (bd >> 32) + (ad & kM32) + (bc & kM32);
    tmp += 1U << 31;
    uint64_t result_f = ac + (ad >> 32) + (bc >> 32) + (tmp >> 32);
    e_ += other.e_ + 64;
    f_ = result_f;
  }

  static DiyFp Times(const DiyFp& a, const DiyFp& b) {
    DiyFp result = a;
    result.Multiply(b);
    return result;
  }

  void Normalize() {
    assert(f_ != 0);
    uint64_t significand = f_;
    int exponent = e_;

    const uint64_t k10MSBits = 0xFFC0000000000000ULL;
    while ((significand & k10MSBits) == 0) {
      significand <<= 10;
      exponent -= 10;
    }
    while ((significand & kUint64MSB) == 0) {
      significand <<= 1;
      exponent--;
    }
    f_ = significand;
    e_ = exponent;
  }

  static DiyFp Normalize(const DiyFp& a) {
    DiyFp result = a;
    result.Normalize();
    return result;
  }

  uint64_t f() const { return f_; }
  int e() const { return e_; }

  void set_f(uint64_t new_value) { f_ = new_value; }
  void set_e(int new_value) { e_ = new_value; }

 private:
  static const uint64_t kUint64MSB = 0x8000000000000000ULL;

  uint64_t f_;
  int e_;
};


template <class Dest, class Source>
inline Dest bit_cast(const Source& source) {
  static_assert(sizeof(Dest) == sizeof(Source), "Dest and Source need to have the same size");

  Dest dest;
  memmove(&dest, &source, sizeof(dest));
  return dest;
}


enum FastDtoaMode {
  FAST_DTOA_SHORTEST,
  FAST_DTOA_SHORTEST_SINGLE,
  FAST_DTOA_PRECISION
};

static const int kFastDtoaMaximalLength = 17;
static const int kFastDtoaMaximalSingleLength = 9;

struct CachedPower {
  uint64_t significand;
  int16_t binary_exponent;
  int16_t decimal_exponent;
};

inline void GetCachedPowerForBinaryExponentRange(int min_exponent, int max_exponent, DiyFp* power, int* decimal_exponent) {
  static const CachedPower kCachedPowers[] = {
    {0xfa8fd5a0081c0288ULL, -1220, -348},
    {0xbaaee17fa23ebf76ULL, -1193, -340},
    {0x8b16fb203055ac76ULL, -1166, -332},
    {0xcf42894a5dce35eaULL, -1140, -324},
    {0x9a6bb0aa55653b2dULL, -1113, -316},
    {0xe61acf033d1a45dfULL, -1087, -308},
    {0xab70fe17c79ac6caULL, -1060, -300},
    {0xff77b1fcbebcdc4fULL, -1034, -292},
    {0xbe5691ef416bd60cULL, -1007, -284},
    {0x8dd01fad907ffc3cULL, -980, -276},
    {0xd3515c2831559a83ULL, -954, -268},
    {0x9d71ac8fada6c9b5ULL, -927, -260},
    {0xea9c227723ee8bcbULL, -901, -252},
    {0xaecc49914078536dULL, -874, -244},
    {0x823c12795db6ce57ULL, -847, -236},
    {0xc21094364dfb5637ULL, -821, -228},
    {0x9096ea6f3848984fULL, -794, -220},
    {0xd77485cb25823ac7ULL, -768, -212},
    {0xa086cfcd97bf97f4ULL, -741, -204},
    {0xef340a98172aace5ULL, -715, -196},
    {0xb23867fb2a35b28eULL, -688, -188},
    {0x84c8d4dfd2c63f3bULL, -661, -180},
    {0xc5dd44271ad3cdbaULL, -635, -172},
    {0x936b9fcebb25c996ULL, -608, -164},
    {0xdbac6c247d62a584ULL, -582, -156},
    {0xa3ab66580d5fdaf6ULL, -555, -148},
    {0xf3e2f893dec3f126ULL, -529, -140},
    {0xb5b5ada8aaff80b8ULL, -502, -132},
    {0x87625f056c7c4a8bULL, -475, -124},
    {0xc9bcff6034c13053ULL, -449, -116},
    {0x964e858c91ba2655ULL, -422, -108},
    {0xdff9772470297ebdULL, -396, -100},
    {0xa6dfbd9fb8e5b88fULL, -369, -92},
    {0xf8a95fcf88747d94ULL, -343, -84},
    {0xb94470938fa89bcfULL, -316, -76},
    {0x8a08f0f8bf0f156bULL, -289, -68},
    {0xcdb02555653131b6ULL, -263, -60},
    {0x993fe2c6d07b7facULL, -236, -52},
    {0xe45c10c42a2b3b06ULL, -210, -44},
    {0xaa242499697392d3ULL, -183, -36},
    {0xfd87b5f28300ca0eULL, -157, -28},
    {0xbce5086492111aebULL, -130, -20},
    {0x8cbccc096f5088ccULL, -103, -12},
    {0xd1b71758e219652cULL, -77, -4},
    {0x9c40000000000000ULL, -50, 4},
    {0xe8d4a51000000000ULL, -24, 12},
    {0xad78ebc5ac620000ULL, 3, 20},
    {0x813f3978f8940984ULL, 30, 28},
    {0xc097ce7bc90715b3ULL, 56, 36},
    {0x8f7e32ce7bea5c70ULL, 83, 44},
    {0xd5d238a4abe98068ULL, 109, 52},
    {0x9f4f2726179a2245ULL, 136, 60},
    {0xed63a231d4c4fb27ULL, 162, 68},
    {0xb0de65388cc8ada8ULL, 189, 76},
    {0x83c7088e1aab65dbULL, 216, 84},
    {0xc45d1df942711d9aULL, 242, 92},
    {0x924d692ca61be758ULL, 269, 100},
    {0xda01ee641a708deaULL, 295, 108},
    {0xa26da3999aef774aULL, 322, 116},
    {0xf209787bb47d6b85ULL, 348, 124},
    {0xb454e4a179dd1877ULL, 375, 132},
    {0x865b86925b9bc5c2ULL, 402, 140},
    {0xc83553c5c8965d3dULL, 428, 148},
    {0x952ab45cfa97a0b3ULL, 455, 156},
    {0xde469fbd99a05fe3ULL, 481, 164},
    {0xa59bc234db398c25ULL, 508, 172},
    {0xf6c69a72a3989f5cULL, 534, 180},
    {0xb7dcbf5354e9beceULL, 561, 188},
    {0x88fcf317f22241e2ULL, 588, 196},
    {0xcc20ce9bd35c78a5ULL, 614, 204},
    {0x98165af37b2153dfULL, 641, 212},
    {0xe2a0b5dc971f303aULL, 667, 220},
    {0xa8d9d1535ce3b396ULL, 694, 228},
    {0xfb9b7cd9a4a7443cULL, 720, 236},
    {0xbb764c4ca7a44410ULL, 747, 244},
    {0x8bab8eefb6409c1aULL, 774, 252},
    {0xd01fef10a657842cULL, 800, 260},
    {0x9b10a4e5e9913129ULL, 827, 268},
    {0xe7109bfba19c0c9dULL, 853, 276},
    {0xac2820d9623bf429ULL, 880, 284},
    {0x80444b5e7aa7cf85ULL, 907, 292},
    {0xbf21e44003acdd2dULL, 933, 300},
    {0x8e679c2f5e44ff8fULL, 960, 308},
    {0xd433179d9c8cb841ULL, 986, 316},
    {0x9e19db92b4e31ba9ULL, 1013, 324},
    {0xeb96bf6ebadf77d9ULL, 1039, 332},
    {0xaf87023b9bf0ee6bULL, 1066, 340},
  };

  static const int kDecimalExponentDistance = 8;
  int kQ = DiyFp::kSignificandSize;
  static const double kD_1_LOG2_10 = 0.30102999566398114;
  double k = ceil((min_exponent + kQ - 1) * kD_1_LOG2_10);
  static const int kCachedPowersOffset = 348;
  int foo = kCachedPowersOffset;
  int index = (foo + int(k) - 1) / kDecimalExponentDistance + 1;
  assert(0 <= index && index < int(ARRAY_SIZE(kCachedPowers)));
  CachedPower cached_power = kCachedPowers[index];
  assert(min_exponent <= cached_power.binary_exponent);
  (void) max_exponent;  assert(cached_power.binary_exponent <= max_exponent);
  *decimal_exponent = cached_power.decimal_exponent;
  *power = DiyFp(cached_power.significand, cached_power.binary_exponent);
}


class Double {
 public:
  static const uint64_t kSignMask = 0x8000000000000000ULL;
  static const uint64_t kExponentMask = 0x7FF0000000000000ULL;
  static const uint64_t kSignificandMask = 0x000FFFFFFFFFFFFFULL;
  static const uint64_t kHiddenBit = 0x0010000000000000ULL;
  static const int kPhysicalSignificandSize = 52;
  static const int kSignificandSize = 53;

  explicit Double(double d) 
    : data(bit_cast<uint64_t>(d)) {}

  DiyFp AsDiyFp() const {
    assert(Sign() > 0);
    assert(!IsSpecial());
    return DiyFp(Significand(), Exponent());
  }

  DiyFp AsNormalizedDiyFp() const {
    assert(value() > 0.0);
    uint64_t f = Significand();
    int e = Exponent();

    while ((f & kHiddenBit) == 0) {
      f <<= 1;
      e--;
    }
    f <<= DiyFp::kSignificandSize - kSignificandSize;
    e -= DiyFp::kSignificandSize - kSignificandSize;
    return DiyFp(f, e);
  }

  int Exponent() const {
    if (IsDenormal()) return kDenormalExponent;

    int biased_e = int((data & kExponentMask) >> kPhysicalSignificandSize);
    return biased_e - kExponentBias;
  }

  uint64_t Significand() const {
    uint64_t significand = data & kSignificandMask;
    if (!IsDenormal()) {
      return significand + kHiddenBit;
    } else {
      return significand;
    }
  }

  bool IsDenormal() const {
    return (data & kExponentMask) == 0;
  }

  bool IsSpecial() const {
    return (data & kExponentMask) == kExponentMask;
  }

  int Sign() const {
    return (data & kSignMask) == 0? 1: -1;
  }

  void NormalizedBoundaries(DiyFp* out_m_minus, DiyFp* out_m_plus) const {
    assert(value() > 0.0);
    DiyFp v = this->AsDiyFp();
    DiyFp m_plus = DiyFp::Normalize(DiyFp((v.f() << 1) + 1, v.e() - 1));
    DiyFp m_minus;
    if (LowerBoundaryIsCloser()) {
      m_minus = DiyFp((v.f() << 2) - 1, v.e() - 2);
    } else {
      m_minus = DiyFp((v.f() << 1) - 1, v.e() - 1);
    }
    m_minus.set_f(m_minus.f() << (m_minus.e() - m_plus.e()));
    m_minus.set_e(m_plus.e());
    *out_m_plus = m_plus;
    *out_m_minus = m_minus;
  }

  bool LowerBoundaryIsCloser() const {
    bool physical_significand_is_zero = ((data & kSignificandMask) == 0);
    return physical_significand_is_zero && (Exponent() != kDenormalExponent);
  }

  double value() const { return bit_cast<double>(data); }

 private:
  static const int kExponentBias = 0x3FF + kPhysicalSignificandSize;
  static const int kDenormalExponent = -kExponentBias + 1;
  static const int kMaxExponent = 0x7FF - kExponentBias;
  static const uint64_t kInfinity = 0x7FF0000000000000ULL;
  static const uint64_t kNaN = 0x7FF8000000000000ULL;

  const uint64_t data;

  Double() = delete;
  Double(Double const&) = delete;
  Double& operator=(Double const&) = delete;
  Double(Double&&) = delete;
  Double& operator=(Double&&) = delete;
};

class Single {
 public:
  static const uint32_t kSignMask = 0x80000000;
  static const uint32_t kExponentMask = 0x7F800000;
  static const uint32_t kSignificandMask = 0x007FFFFF;
  static const uint32_t kHiddenBit = 0x00800000;
  static const int kPhysicalSignificandSize = 23;
  static const int kSignificandSize = 24;

  explicit Single(float f)
    : data(bit_cast<uint32_t>(f)) {}

  DiyFp AsDiyFp() const {
    assert(Sign() > 0);
    assert(!IsSpecial());
    return DiyFp(Significand(), Exponent());
  }

  int Exponent() const {
    if (IsDenormal()) {
      return kDenormalExponent;
    }

    int biased_e =int((data & kExponentMask) >> kPhysicalSignificandSize);
    return biased_e - kExponentBias;
  }

  uint32_t Significand() const {
    uint32_t significand = data & kSignificandMask;
    if (!IsDenormal()) {
      return significand + kHiddenBit;
    } else {
      return significand;
    }
  }

  bool IsDenormal() const {
    return (data & kExponentMask) == 0;
  }

  bool IsSpecial() const {
    return (data & kExponentMask) == kExponentMask;
  }

  int Sign() const {
    return (data & kSignMask) == 0? 1: -1;
  }

  void NormalizedBoundaries(DiyFp* out_m_minus, DiyFp* out_m_plus) const {
    assert(value() > 0.0);
    DiyFp v = this->AsDiyFp();
    DiyFp m_plus = DiyFp::Normalize(DiyFp((v.f() << 1) + 1, v.e() - 1));
    DiyFp m_minus;
    if (LowerBoundaryIsCloser()) {
      m_minus = DiyFp((v.f() << 2) - 1, v.e() - 2);
    } else {
      m_minus = DiyFp((v.f() << 1) - 1, v.e() - 1);
    }
    m_minus.set_f(m_minus.f() << (m_minus.e() - m_plus.e()));
    m_minus.set_e(m_plus.e());
    *out_m_plus = m_plus;
    *out_m_minus = m_minus;
  }

  bool LowerBoundaryIsCloser() const {
    bool physical_significand_is_zero = ((data & kSignificandMask) == 0);
    return physical_significand_is_zero && (Exponent() != kDenormalExponent);
  }

  float value() const { return bit_cast<float>(data); }


 private:
  static const int kExponentBias = 0x7F + kPhysicalSignificandSize;
  static const int kDenormalExponent = -kExponentBias + 1;
  static const int kMaxExponent = 0xFF - kExponentBias;
  static const uint32_t kInfinity = 0x7F800000;
  static const uint32_t kNaN = 0x7FC00000;

  const uint32_t data;

  Single() = delete;
  Single(Single const&) = delete;
  Single& operator=(Single const&) = delete;
  Single(Single&&) = delete;
  Single& operator=(Single&&) = delete;
};



static const int kMinimalTargetExponent = -60;
static const int kMaximalTargetExponent = -32;

inline bool RoundWeed(Vector<char> buffer, int length, uint64_t distance_too_high_w, uint64_t unsafe_interval, uint64_t rest, uint64_t ten_kappa, uint64_t unit) {

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

inline bool RoundWeedCounted(Vector<char> buffer,
                             int length,
                             uint64_t rest,
                             uint64_t ten_kappa,
                             uint64_t unit,
                             int* kappa) {
  assert(rest < ten_kappa);
  if (unit >= ten_kappa) return false;
  if (ten_kappa - unit <= unit) return false;
  if ((ten_kappa - rest > rest) && (ten_kappa - 2 * rest >= 2 * unit)) {
    return true;
  }
  if ((rest > unit) && (ten_kappa - (rest - unit) <= (rest - unit))) {
    buffer[length - 1]++;
    for (int i = length - 1; i > 0; --i) {
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

static unsigned int const kSmallPowersOfTen[] = {0, 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

inline void BiggestPowerTen(uint32_t number, int number_bits, uint32_t* power, int* exponent_plus_one) {
  assert(number < (1u << (number_bits + 1)));
  int exponent_plus_one_guess = ((number_bits + 1) * 1233 >> 12) + 1;

  if (number < kSmallPowersOfTen[exponent_plus_one_guess]) {
    exponent_plus_one_guess--;
  }
  *power = kSmallPowersOfTen[exponent_plus_one_guess];
  *exponent_plus_one = exponent_plus_one_guess;
}

inline bool DigitGen(DiyFp low, DiyFp w, DiyFp high, Vector<char> buffer, int* length, int* kappa) {
  assert(low.e() == w.e() && w.e() == high.e());
  assert(low.f() + 1 <= high.f() - 1);
  assert(kMinimalTargetExponent <= w.e() && w.e() <= kMaximalTargetExponent);
  uint64_t unit = 1;
  DiyFp too_low = DiyFp(low.f() - unit, low.e());
  DiyFp too_high = DiyFp(high.f() + unit, high.e());
  DiyFp unsafe_interval = DiyFp::Minus(too_high, too_low);
  DiyFp one = DiyFp(1ULL << -w.e(), w.e());
  uint32_t integrals = uint32_t(too_high.f() >> -one.e());
  uint64_t fractionals = too_high.f() & (one.f() - 1ULL);
  uint32_t divisor;
  int divisor_exponent_plus_one;

  BiggestPowerTen(integrals, DiyFp::kSignificandSize - (-one.e()), &divisor, &divisor_exponent_plus_one);

  *kappa = divisor_exponent_plus_one;
  *length = 0;
  while (*kappa > 0) {
    int digit = integrals / divisor;
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    integrals %= divisor;
    (*kappa)--;
    uint64_t rest = (uint64_t(integrals) << -one.e()) + fractionals;

    if (rest < unsafe_interval.f()) {
      return RoundWeed(buffer, *length, DiyFp::Minus(too_high, w).f(), unsafe_interval.f(), rest, uint64_t(divisor) << -one.e(), unit);
    }
    divisor /= 10;
  }

  assert(one.e() >= -60);
  assert(fractionals < one.f());
  assert(0xFFFFFFFFFFFFFFFFULL / 10 >= one.f());

  for (;;) {
    fractionals *= 10;
    unit *= 10;
    unsafe_interval.set_f(unsafe_interval.f() * 10);
    int digit = int(fractionals >> -one.e());
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    fractionals &= one.f() - 1;
    (*kappa)--;
    if (fractionals < unsafe_interval.f()) {
      return RoundWeed(buffer, *length, DiyFp::Minus(too_high, w).f() * unit, unsafe_interval.f(), fractionals, one.f(), unit);
    }
  }
}

inline bool DigitGenCounted(DiyFp w, int requested_digits, Vector<char> buffer, int* length, int* kappa) {
  assert(kMinimalTargetExponent <= w.e() && w.e() <= kMaximalTargetExponent);
  assert(kMinimalTargetExponent >= -60);
  assert(kMaximalTargetExponent <= -32);
  uint64_t w_error = 1;
  DiyFp one = DiyFp(1ULL << -w.e(), w.e());
  uint32_t integrals = uint32_t(w.f() >> -one.e());
  uint64_t fractionals = w.f() & (one.f() - 1);
  uint32_t divisor;
  int divisor_exponent_plus_one;
  BiggestPowerTen(integrals, DiyFp::kSignificandSize - (-one.e()), &divisor, &divisor_exponent_plus_one);
  *kappa = divisor_exponent_plus_one;
  *length = 0;

  while (*kappa > 0) {
    int digit = integrals / divisor;
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    requested_digits--;
    integrals %= divisor;
    (*kappa)--;
    if (requested_digits == 0) break;
    divisor /= 10;
  }

  if (requested_digits == 0) {
    uint64_t rest = (uint64_t(integrals) << -one.e()) + fractionals;
    return RoundWeedCounted(buffer, *length, rest, uint64_t(divisor) << -one.e(), w_error, kappa);
  }

  assert(one.e() >= -60);
  assert(fractionals < one.f());
  assert(0xFFFFFFFFFFFFFFFFULL / 10 >= one.f());

  while (requested_digits > 0 && fractionals > w_error) {
    fractionals *= 10;
    w_error *= 10;
    int digit = int(fractionals >> -one.e());
    assert(digit <= 9);
    buffer[*length] = char('0' + digit);
    (*length)++;
    requested_digits--;
    fractionals &= one.f() - 1;
    (*kappa)--;
  }

  if (requested_digits != 0)
    return false;

  return RoundWeedCounted(buffer, *length, fractionals, one.f(), w_error, kappa);
}

inline bool Grisu3(double v, FastDtoaMode mode, Vector<char> buffer, int* length, int* decimal_exponent) {
  DiyFp w = Double(v).AsNormalizedDiyFp();
  DiyFp boundary_minus, boundary_plus;
  if (mode == FAST_DTOA_SHORTEST) {
    Double(v).NormalizedBoundaries(&boundary_minus, &boundary_plus);
  } else {
    assert(mode == FAST_DTOA_SHORTEST_SINGLE);
    float single_v = float(v);
    Single(single_v).NormalizedBoundaries(&boundary_minus, &boundary_plus);
  }
  assert(boundary_plus.e() == w.e());
  DiyFp ten_mk;  int mk;  int ten_mk_minimal_binary_exponent = kMinimalTargetExponent - (w.e() + DiyFp::kSignificandSize);
  int ten_mk_maximal_binary_exponent = kMaximalTargetExponent - (w.e() + DiyFp::kSignificandSize);
  GetCachedPowerForBinaryExponentRange( ten_mk_minimal_binary_exponent, ten_mk_maximal_binary_exponent, &ten_mk, &mk);
  assert((kMinimalTargetExponent <= w.e() + ten_mk.e() + DiyFp::kSignificandSize) && (kMaximalTargetExponent >= w.e() + ten_mk.e() + DiyFp::kSignificandSize));
  DiyFp scaled_w = DiyFp::Times(w, ten_mk);
  assert(scaled_w.e() == boundary_plus.e() + ten_mk.e() + DiyFp::kSignificandSize);
  DiyFp scaled_boundary_minus = DiyFp::Times(boundary_minus, ten_mk);
  DiyFp scaled_boundary_plus  = DiyFp::Times(boundary_plus,  ten_mk);

  int kappa;
  bool result = DigitGen(scaled_boundary_minus, scaled_w, scaled_boundary_plus, buffer, length, &kappa);
  *decimal_exponent = -mk + kappa;
  return result;
}


inline bool Grisu3Counted(double v, int requested_digits, Vector<char> buffer, int* length, int* decimal_exponent) {
  DiyFp w = Double(v).AsNormalizedDiyFp();
  DiyFp ten_mk;
  int mk;
  int ten_mk_minimal_binary_exponent = kMinimalTargetExponent - (w.e() + DiyFp::kSignificandSize);
  int ten_mk_maximal_binary_exponent = kMaximalTargetExponent - (w.e() + DiyFp::kSignificandSize);
  GetCachedPowerForBinaryExponentRange( ten_mk_minimal_binary_exponent, ten_mk_maximal_binary_exponent, &ten_mk, &mk);
  assert((kMinimalTargetExponent <= w.e() + ten_mk.e() + DiyFp::kSignificandSize) && (kMaximalTargetExponent >= w.e() + ten_mk.e() + DiyFp::kSignificandSize));
  DiyFp scaled_w = DiyFp::Times(w, ten_mk);

  int kappa;
  bool result = DigitGenCounted(scaled_w, requested_digits, buffer, length, &kappa);
  *decimal_exponent = -mk + kappa;
  return result;
}


inline bool FastDtoa(double v, FastDtoaMode mode, int requested_digits, Vector<char> buffer, int* length, int* decimal_point) {
  assert(v > 0);
  assert(!Double(v).IsSpecial());

  bool result = false;
  int decimal_exponent = 0;
  switch (mode) {
    case FAST_DTOA_SHORTEST:
    case FAST_DTOA_SHORTEST_SINGLE:
      result = Grisu3(v, mode, buffer, length, &decimal_exponent);
      break;
    case FAST_DTOA_PRECISION:
      result = Grisu3Counted(v, requested_digits, buffer, length, &decimal_exponent);
      break;
    default:
      unreachable();
  }
  if (result) {
    *decimal_point = *length + decimal_exponent;
    buffer[*length] = '\0';
  }
  return result;
}

