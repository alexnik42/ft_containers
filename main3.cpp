#include "ft_containers-unit-test/sources/system/system_methods.ipp"
#include "ft_containers-unit-test/sources/vector_tests/__service.ipp"

template <typename T>
std::vector<int> swap_test(std::vector<T> vector) {
  _ratio = 1;
  std::vector<int> v;
  vector.assign(1100 * _ratio, 11);
  std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10),
      tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
  g_start1 = timer();
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  long *adr1 = reinterpret_cast<long *>(&vector);
  long *adr2 = reinterpret_cast<long *>(&tmp);
  vector.swap(tmp);
  if (reinterpret_cast<long *>(&vector) == adr1 &&
      reinterpret_cast<long *>(&tmp) == adr2)
    v.push_back(1);
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.swap(tmp3);

  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  std::swap(vector, tmp2);
  v.push_back(vector[2]);
  v.push_back(vector.size());
  std::cout << "\ncapacity (original): " << vector.capacity() << std::endl;
  v.push_back(vector.capacity());
  std::swap(vector, tmp4);
  std::cout << "\nAfter tmp4 (original):\n";
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  g_end1 = timer();
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  return v;
}

template <typename T>
std::vector<int> swap_test(_vector<T> vector) {
  _ratio = 1;
  std::vector<int> v;
  vector.assign(1100 * _ratio, 11);
  _vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10),
      tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
  g_start2 = timer();
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  long *adr1 = reinterpret_cast<long *>(&vector);
  long *adr2 = reinterpret_cast<long *>(&tmp);
  vector.swap(tmp);
  if (reinterpret_cast<long *>(&vector) == adr1 &&
      reinterpret_cast<long *>(&tmp) == adr2)
    v.push_back(1);
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  vector.swap(tmp3);
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
//   vector.swap(tmp2);
  std::swap(vector, tmp2);
  v.push_back(vector[2]);
  v.push_back(vector.size());
  std::cout << "\ncapacity (mine): " << vector.capacity() << std::endl;
  v.push_back(vector.capacity());
  std::swap(vector, tmp4);
    std::cout << "\nAfter tmp4 (mine):\n";
  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  g_end2 = timer();
  v.push_back(vector[2]);
  v.push_back(vector.size());
  v.push_back(vector.capacity());
  return v;
}

int main() {
  // std::vector<int> original;
  // ft::Vector<int> mine;

  // std::vector<int> originalNew = swap_test(original);
  // std::vector<int> mineNew = swap_test(original);

  // for (size_t i = 0; i < originalNew.size(); i++) {
  // 	std::cout << originalNew[i] << " ";
  // }
  // std::cout << std::endl;

  // for (size_t i = 0; i < mineNew.size(); i++) {
  // 	std::cout << mineNew[i] << " ";
  // }
  // std::cout << std::endl;

  exit(run_vector_unit_test<int>("swap()", swap_test, swap_test));
}