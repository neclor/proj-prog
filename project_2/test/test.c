#include "seatest.h"
#include "pnm.h"
#include "filter.h"

/* ======= Constants ======= */

const char *image_pbm_path = "test_image/image.pbm";
const char *image_pgm_path = "test_image/image.pgm";
const char *image_ppm_path = "test_image/image.ppm";

const char *result_pbm_path = "test_image/result.pbm";
const char *result_pgm_path = "test_image/result.pgm";
const char *result_ppm_path = "test_image/result.ppm";

/* ======= Functions ======= */

static void test_load_pnm() {
   PNM *image = NULL;

   assert_true(load_pnm(NULL, image_pbm_path) < 0);
   assert_true(load_pnm(&image, NULL) < 0);

   assert_int_equal(load_pnm(&image, "abc"), PNM_INVALID_FILENAME);

   assert_int_equal(load_pnm(&image, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(get_format(image), FORMAT_PBM);
   assert_int_equal(get_width(image), 3);
   assert_int_equal(get_height(image), 3);
   assert_int_equal(get_max_value(image), PBM_MAX_VALUE);
   for (size_t i = 0; i < get_width(image) * get_height(image); ++i) {
      assert_int_equal(get_data(image)[i], PBM_MAX_VALUE);
   }
   free_pnm(&image);

   assert_int_equal(PNM_SUCCESS, load_pnm(&image, image_pgm_path));
   assert_int_equal(get_format(image), FORMAT_PGM);
   assert_int_equal(get_width(image), 3);
   assert_int_equal(get_height(image), 3);
   assert_int_equal(get_max_value(image), PGM_MAX_VALUE);
   for (size_t i = 0; i < get_width(image) * get_height(image); ++i) {
      assert_int_equal(get_data(image)[i], PGM_MAX_VALUE);
   }
   free_pnm(&image);

   assert_int_equal(PNM_SUCCESS, load_pnm(&image, image_ppm_path));
   assert_int_equal(get_format(image), FORMAT_PPM);
   assert_int_equal(get_width(image), 3);
   assert_int_equal(get_height(image), 3);
   assert_int_equal(get_max_value(image), PPM_MAX_VALUE);
   for (size_t i = 0; i < get_width(image) * get_height(image) * 3; ++i) {
      assert_int_equal(get_data(image)[i], PPM_MAX_VALUE);
   }
   free_pnm(&image);
}

static void test_write_pnm() {
   PNM *image_pbm = NULL;
   PNM *image_pgm = NULL;
   PNM *image_ppm = NULL;
   assert_int_equal(load_pnm(&image_pbm, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(load_pnm(&image_pgm, image_pgm_path), PNM_SUCCESS);
   assert_int_equal(load_pnm(&image_ppm, image_ppm_path), PNM_SUCCESS);

   assert_true(write_pnm(NULL, result_pbm_path) < 0);
   assert_true(write_pnm(image_pbm, NULL) < 0);

   assert_int_equal(write_pnm(image_pbm, "<>abc.pbm"), PNM_INVALID_FILENAME);
   assert_int_equal(write_pnm(image_pbm, "abc"), PNM_INVALID_FILENAME);

   assert_int_equal(write_pnm(image_pbm, result_pbm_path), PNM_SUCCESS);
   PNM *result_pbm = NULL;
   assert_int_equal(load_pnm(&result_pbm, result_pbm_path), PNM_SUCCESS);
   assert_int_equal(get_format(image_pbm), get_format(result_pbm));
   assert_int_equal(get_width(image_pbm), get_width(result_pbm));
   assert_int_equal(get_height(image_pbm), get_height(result_pbm));
   assert_int_equal(get_max_value(image_pbm), get_max_value(result_pbm));
   for (size_t i = 0; i < get_width(image_pbm) * get_height(image_pbm); ++i) {
      assert_int_equal(get_data(image_pbm)[i], get_data(result_pbm)[i]);
   }
   free_pnm(&image_pbm);
   free_pnm(&result_pbm);

   assert_int_equal(write_pnm(image_pgm, result_pgm_path), PNM_SUCCESS);
   PNM *result_pgm = NULL;
   assert_int_equal(load_pnm(&result_pgm, result_pgm_path), PNM_SUCCESS);
   assert_int_equal(get_format(image_pgm), get_format(result_pgm));
   assert_int_equal(get_width(image_pgm), get_width(result_pgm));
   assert_int_equal(get_height(image_pgm), get_height(result_pgm));
   assert_int_equal(get_max_value(image_pgm), get_max_value(result_pgm));
   for (size_t i = 0; i < get_width(image_pgm) * get_height(image_pgm); ++i) {
      assert_int_equal(get_data(image_pgm)[i], get_data(result_pgm)[i]);
   }
   free_pnm(&image_pgm);
   free_pnm(&result_pgm);

   assert_int_equal(write_pnm(image_ppm, result_ppm_path), PNM_SUCCESS);
   PNM *result_ppm = NULL;
   assert_int_equal(load_pnm(&result_ppm, result_ppm_path), PNM_SUCCESS);
   assert_int_equal(get_format(image_ppm), get_format(result_ppm));
   assert_int_equal(get_width(image_ppm), get_width(result_ppm));
   assert_int_equal(get_height(image_ppm), get_height(result_ppm));
   assert_int_equal(get_max_value(image_ppm), get_max_value(result_ppm));
   for (size_t i = 0; i < get_width(image_ppm) * get_height(image_ppm) * 3; ++i) {
      assert_int_equal(get_data(image_ppm)[i], get_data(result_ppm)[i]);
   }
   free_pnm(&image_ppm);
   free_pnm(&result_ppm);
}

static void test_turnaround() {
   assert_true(turnaround(NULL) < 0);

   PNM *image_orig = NULL;
   assert_int_equal(load_pnm(&image_orig, image_pbm_path), PNM_SUCCESS);
   PNM *image_modif = NULL;
   assert_int_equal(load_pnm(&image_modif, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(turnaround(image_modif), FILTER_SUCCESS);

   assert_int_equal(get_width(image_orig), get_width(image_modif));
   assert_int_equal(get_height(image_orig), get_height(image_modif));

   size_t data_size = get_width(image_orig) * get_height(image_orig);

   for (size_t i = 0; i < data_size / 2; ++i) {
      size_t j = data_size - 1 - i;
      assert_int_equal(get_data(image_orig)[i], get_data(image_modif)[j]);
   }
   free_pnm(&image_orig);
   free_pnm(&image_modif);
}

static void test_monochrome() {
   assert_true(monochrome(NULL, "r") < 0);

   PNM *image = NULL;
   assert_int_equal(load_pnm(&image, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(monochrome(image, "r"), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_pgm_path), PNM_SUCCESS);
   assert_int_equal(monochrome(image, "r"), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_ppm_path), PNM_SUCCESS);
   assert_int_equal(monochrome(image, NULL), FILTER_INVALID_PARAMETER);
   assert_int_equal(monochrome(image, "abc"), FILTER_INVALID_PARAMETER);

   assert_int_equal(monochrome(image, "r"), FILTER_SUCCESS);
   free_pnm(&image);
}

static void test_negative() {
   assert_true(negative(NULL) < 0);

   PNM *image = NULL;
   assert_int_equal(load_pnm(&image, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(negative(image), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_pgm_path), PNM_SUCCESS);
   assert_int_equal(negative(image), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_ppm_path), PNM_SUCCESS);
   assert_int_equal(negative(image), FILTER_SUCCESS);
   free_pnm(&image);
}

static void test_fifty_shades_of_grey() {
   assert_true(fifty_shades_of_grey(NULL, "1") < 0);

   PNM *image = NULL;
   assert_int_equal(load_pnm(&image, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(fifty_shades_of_grey(image, "1"), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_pgm_path), PNM_SUCCESS);
   assert_int_equal(fifty_shades_of_grey(image, "1"), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_ppm_path), PNM_SUCCESS);
   assert_int_equal(fifty_shades_of_grey(image, NULL), FILTER_INVALID_PARAMETER);
   assert_int_equal(fifty_shades_of_grey(image, "3"), FILTER_INVALID_PARAMETER);

   assert_int_equal(fifty_shades_of_grey(image, "1"), FILTER_SUCCESS);
   assert_int_equal(get_format(image), FORMAT_PGM);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_ppm_path), PNM_SUCCESS);
   assert_int_equal(fifty_shades_of_grey(image, "2"), FILTER_SUCCESS);
   assert_int_equal(get_format(image), FORMAT_PGM);
   free_pnm(&image);
}

static void test_black_and_white() {
   assert_true(black_and_white(NULL, "128") < 0);

   PNM *image = NULL;
   assert_int_equal(load_pnm(&image, image_pbm_path), PNM_SUCCESS);
   assert_int_equal(black_and_white(image, "128"), FILTER_WRONG_IMAGE_FORMAT);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_pgm_path), PNM_SUCCESS);
   assert_int_equal(black_and_white(image, NULL), FILTER_INVALID_PARAMETER);
   assert_int_equal(black_and_white(image, "-1"), FILTER_INVALID_PARAMETER);
   assert_int_equal(black_and_white(image, "256"), FILTER_INVALID_PARAMETER);
   assert_int_equal(black_and_white(image, "128"), FILTER_SUCCESS);
   assert_int_equal(get_format(image), FORMAT_PBM);
   free_pnm(&image);

   assert_int_equal(load_pnm(&image, image_ppm_path), PNM_SUCCESS);
   assert_int_equal(black_and_white(image, "128"), FILTER_SUCCESS);
   assert_int_equal(get_format(image), FORMAT_PBM);
   free_pnm(&image);
}

static void test_fixture() {
   test_fixture_start();
   run_test(test_load_pnm);
   run_test(test_write_pnm);
   run_test(test_turnaround);
   run_test(test_monochrome);
   run_test(test_negative);
   run_test(test_fifty_shades_of_grey);
   run_test(test_black_and_white);
   test_fixture_end();
}

static void all_tests() {
   test_fixture();
}

int main() {
   return run_tests(all_tests);
}
