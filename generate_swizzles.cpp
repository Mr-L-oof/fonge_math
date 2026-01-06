#include <cmath>
#include <stdlib.h>
#include <cstdint>
#include <array>
#include <string>
#include <vector>
#include <set>

const char CHARIDS[8] = {'x', 'y', 'z', 'w', 'r', 'g', 'b', 'a'};
const std::string primitives[4] = {"float", "double", "int"};
const std::string primitive_conversion_funcs[4] = {"simde_mm_cvtss_f32", "simde_mm256_cvtsd_f64", "simde_mm_cvtsi128_si32"};
const std::string primitive_permute_funcs[4] = {"permute_ps_custom", "permute_pd_custom", "simde_mm_shuffle_epi32"};

std::array<uint32_t, 4> to_base(uint32_t n, uint32_t base) {
    std::array<uint32_t, 4> num_base = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++) {
        num_base[i] = (n % (int)std::pow(base, i+1))/std::pow(base, i);
    }
    return num_base;
}

uint32_t get_or(std::vector<uint32_t> ids, int i, uint32_t fallback) {
    if (i >= ids.size()) {
        return fallback;
    } else {
        return ids[i];
    }
} 

std::string get_swizzle_declaration(std::vector<uint32_t> ids, int type_id) {
    std::string xyz_swizz_name;
    for (auto n : ids) {
        xyz_swizz_name.push_back(CHARIDS[n]);
    }

    std::string rgb_swizz_name;
    for (auto n : ids) {
        rgb_swizz_name.push_back(CHARIDS[n + 4]);
    }

    int x = get_or(ids, 0, 0);
    int y = get_or(ids, 1, 1);
    int z = get_or(ids, 2, 2);
    int w = get_or(ids, 3, 3);
    std::string dst1, dst2;

    dst1 = 
        "inline " + primitives[type_id] + std::to_string( ids.size()) + " " + xyz_swizz_name + "();\n\n";

    dst2 = 
        "inline " + primitives[type_id] + std::to_string(ids.size()) + " " + rgb_swizz_name + "();\n\n";

    return dst1 + dst2;
}

std::string get_swizzle(std::vector<uint32_t> ids, int type_id, int source_type_size) {
    std::string xyz_swizz_name;
    for (auto n : ids) {
        xyz_swizz_name.push_back(CHARIDS[n]);
    }

    std::string rgb_swizz_name;
    for (auto n : ids) {
        rgb_swizz_name.push_back(CHARIDS[n + 4]);
    }

    int x = get_or(ids, 0, 0);
    int y = get_or(ids, 1, 1);
    int z = get_or(ids, 2, 2);
    int w = get_or(ids, 3, 3);
    std::string dst1, dst2;
    if (ids.size() > 1) {
        dst1 = 
            "inline " + primitives[type_id] + std::to_string(ids.size()) + " " + 
                primitives[type_id] + std::to_string(source_type_size) + "::" + xyz_swizz_name + "() { return " + primitive_permute_funcs[type_id] + 
                "(simd, SIMDE_MM_SHUFFLE(" + std::to_string(w) + ", " 
                + std::to_string(z) + ", " + std::to_string(y) + ", " + std::to_string(x) + ")); }\n\n";

        dst2 = 
            "inline " + primitives[type_id] + std::to_string(ids.size()) + " " + 
                primitives[type_id] + std::to_string(source_type_size) + "::" + rgb_swizz_name + "() { return " + primitive_permute_funcs[type_id] + 
                "(simd, SIMDE_MM_SHUFFLE(" + std::to_string(w) + ", " 
                + std::to_string(z) + ", " + std::to_string(y) + ", " + std::to_string(x) + ")); }\n\n";
    } else {
        dst1 = 
            "inline " + primitives[type_id] + std::to_string(ids.size()) + " " + primitives[type_id] + std::to_string(source_type_size) + "::" + xyz_swizz_name + "() { return " + 
                primitive_conversion_funcs[type_id] + "(" + primitive_permute_funcs[type_id] +"(simd, SIMDE_MM_SHUFFLE(" + std::to_string(x) + ", " 
                + std::to_string(x) + ", " + std::to_string(x) + ", " + std::to_string(x) + "))); }\n\n";

        dst2 =
            "inline " + primitives[type_id] + std::to_string(ids.size()) + " " + primitives[type_id] + std::to_string(source_type_size) + "::" + rgb_swizz_name + "() { return " + 
                primitive_conversion_funcs[type_id] + "(" + primitive_permute_funcs[type_id] +"(simd, SIMDE_MM_SHUFFLE(" + std::to_string(x) + ", " 
                + std::to_string(x) + ", " + std::to_string(x) + ", " + std::to_string(x) + "))); }\n\n";
    }

    return dst1 + dst2;
}

int main(void) {
    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < 4; i++) {
            FILE *fp = fopen(("include/fonge/swizzles/" + primitives[t] + std::to_string(i + 1) + "_swizzles_impl").c_str(), "w");
            FILE *fp2 = fopen(("include/fonge/swizzles/" + primitives[t] + std::to_string(i + 1) + "_swizzles_decl").c_str(), "w");
            std::string wstr("\n");
            std::string wstr2("\n");

            std::vector<std::array<uint32_t, 4>> combinations;

            combinations.reserve(pow(i + 1, 4));

            for (int idnum = 0; idnum < (int)pow(i + 1, 4); idnum++) {
                combinations.push_back(to_base(idnum, i + 1));
            }

            for (int j = 0; j < 4; j++) {
                std::set<std::vector<uint32_t>> combinations_j;
                for (int k = 0; k < combinations.size(); k++) {
                    combinations_j.emplace(std::vector<uint32_t>(combinations[k].begin(), combinations[k].begin() + j + 1));
                }

                for (auto combination : combinations_j) {
                    wstr.append(get_swizzle(combination, t, i + 1));
                    wstr2.append(get_swizzle_declaration(combination, t));
                }
            }

            fprintf(fp, "%s", (wstr + "\n").c_str());
            fprintf(fp2, "%s", (wstr2 + "\n").c_str());

            fclose(fp);
        }
    }


    return 0;
}
