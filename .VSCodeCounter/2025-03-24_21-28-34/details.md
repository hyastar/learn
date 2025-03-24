# Details

Date : 2025-03-24 21:28:34

Directory d:\\information\\IOT\\learn\\C\\opensource\\zlog

Total : 117 files,  8379 codes, 1646 comments, 1880 blanks, all 11905 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [C/opensource/zlog/.clang-format](/C/opensource/zlog/.clang-format) | YAML | 8 | 2 | 4 | 14 |
| [C/opensource/zlog/CMakeLists.txt](/C/opensource/zlog/CMakeLists.txt) | cmake | 51 | 0 | 16 | 67 |
| [C/opensource/zlog/README.md](/C/opensource/zlog/README.md) | Markdown | 106 | 0 | 38 | 144 |
| [C/opensource/zlog/cmake/FindUnixem.cmake](/C/opensource/zlog/cmake/FindUnixem.cmake) | cmake | 22 | 0 | 5 | 27 |
| [C/opensource/zlog/cmake/LoadLibraries.cmake](/C/opensource/zlog/cmake/LoadLibraries.cmake) | cmake | 18 | 0 | 5 | 23 |
| [C/opensource/zlog/cmake/toolchain-mingw64.cmake](/C/opensource/zlog/cmake/toolchain-mingw64.cmake) | cmake | 27 | 0 | 13 | 40 |
| [C/opensource/zlog/cpack/CMakeLists.txt](/C/opensource/zlog/cpack/CMakeLists.txt) | cmake | 34 | 0 | 9 | 43 |
| [C/opensource/zlog/cpack/CPackConfig.cmake](/C/opensource/zlog/cpack/CPackConfig.cmake) | cmake | 34 | 0 | 13 | 47 |
| [C/opensource/zlog/cpack/zlog/CMakeLists.txt](/C/opensource/zlog/cpack/zlog/CMakeLists.txt) | cmake | 23 | 0 | 7 | 30 |
| [C/opensource/zlog/doc/zlog.conf](/C/opensource/zlog/doc/zlog.conf) | Properties | 25 | 1 | 11 | 37 |
| [C/opensource/zlog/src/CMakeLists.txt](/C/opensource/zlog/src/CMakeLists.txt) | cmake | 47 | 0 | 12 | 59 |
| [C/opensource/zlog/src/buf.c](/C/opensource/zlog/src/buf.c) | C | 456 | 136 | 65 | 657 |
| [C/opensource/zlog/src/buf.h](/C/opensource/zlog/src/buf.h) | C++ | 32 | 19 | 13 | 64 |
| [C/opensource/zlog/src/category.c](/C/opensource/zlog/src/category.c) | C | 173 | 36 | 32 | 241 |
| [C/opensource/zlog/src/category.h](/C/opensource/zlog/src/category.h) | C++ | 22 | 14 | 9 | 45 |
| [C/opensource/zlog/src/category\_table.c](/C/opensource/zlog/src/category_table.c) | C | 96 | 20 | 21 | 137 |
| [C/opensource/zlog/src/category\_table.h](/C/opensource/zlog/src/category_table.h) | C++ | 14 | 15 | 7 | 36 |
| [C/opensource/zlog/src/conf.c](/C/opensource/zlog/src/conf.c) | C | 624 | 71 | 85 | 780 |
| [C/opensource/zlog/src/conf.h](/C/opensource/zlog/src/conf.h) | C++ | 32 | 14 | 12 | 58 |
| [C/opensource/zlog/src/event.c](/C/opensource/zlog/src/event.c) | C | 119 | 46 | 29 | 194 |
| [C/opensource/zlog/src/event.h](/C/opensource/zlog/src/event.h) | C++ | 66 | 14 | 20 | 100 |
| [C/opensource/zlog/src/fmacros.h](/C/opensource/zlog/src/fmacros.h) | C++ | 36 | 0 | 7 | 43 |
| [C/opensource/zlog/src/format.c](/C/opensource/zlog/src/format.c) | C | 124 | 23 | 25 | 172 |
| [C/opensource/zlog/src/format.h](/C/opensource/zlog/src/format.h) | C++ | 17 | 14 | 9 | 40 |
| [C/opensource/zlog/src/level.c](/C/opensource/zlog/src/level.c) | C | 108 | 24 | 21 | 153 |
| [C/opensource/zlog/src/level.h](/C/opensource/zlog/src/level.h) | C++ | 14 | 14 | 6 | 34 |
| [C/opensource/zlog/src/level\_list.c](/C/opensource/zlog/src/level_list.c) | C | 108 | 22 | 25 | 155 |
| [C/opensource/zlog/src/level\_list.h](/C/opensource/zlog/src/level_list.h) | C++ | 11 | 21 | 9 | 41 |
| [C/opensource/zlog/src/lockfile.c](/C/opensource/zlog/src/lockfile.c) | C | 38 | 12 | 4 | 54 |
| [C/opensource/zlog/src/lockfile.h](/C/opensource/zlog/src/lockfile.h) | C++ | 21 | 18 | 6 | 45 |
| [C/opensource/zlog/src/mdc.c](/C/opensource/zlog/src/mdc.c) | C | 112 | 17 | 24 | 153 |
| [C/opensource/zlog/src/mdc.h](/C/opensource/zlog/src/mdc.h) | C++ | 21 | 14 | 9 | 44 |
| [C/opensource/zlog/src/record.c](/C/opensource/zlog/src/record.c) | C | 38 | 14 | 9 | 61 |
| [C/opensource/zlog/src/record.h](/C/opensource/zlog/src/record.h) | C++ | 17 | 15 | 8 | 40 |
| [C/opensource/zlog/src/record\_table.c](/C/opensource/zlog/src/record_table.c) | C | 39 | 16 | 9 | 64 |
| [C/opensource/zlog/src/record\_table.h](/C/opensource/zlog/src/record_table.h) | C++ | 8 | 14 | 5 | 27 |
| [C/opensource/zlog/src/rotater.c](/C/opensource/zlog/src/rotater.c) | C | 424 | 39 | 91 | 554 |
| [C/opensource/zlog/src/rotater.h](/C/opensource/zlog/src/rotater.h) | C++ | 25 | 20 | 9 | 54 |
| [C/opensource/zlog/src/rule.c](/C/opensource/zlog/src/rule.c) | C | 852 | 78 | 154 | 1,084 |
| [C/opensource/zlog/src/rule.h](/C/opensource/zlog/src/rule.h) | C++ | 53 | 24 | 19 | 96 |
| [C/opensource/zlog/src/spec.c](/C/opensource/zlog/src/spec.c) | C | 552 | 58 | 103 | 713 |
| [C/opensource/zlog/src/spec.h](/C/opensource/zlog/src/spec.h) | C++ | 37 | 16 | 15 | 68 |
| [C/opensource/zlog/src/thread.c](/C/opensource/zlog/src/thread.c) | C | 144 | 18 | 30 | 192 |
| [C/opensource/zlog/src/thread.h](/C/opensource/zlog/src/thread.h) | C++ | 23 | 14 | 9 | 46 |
| [C/opensource/zlog/src/version.h](/C/opensource/zlog/src/version.h) | C++ | 1 | 0 | 1 | 2 |
| [C/opensource/zlog/src/zc\_arraylist.c](/C/opensource/zlog/src/zc_arraylist.c) | C | 107 | 16 | 17 | 140 |
| [C/opensource/zlog/src/zc\_arraylist.h](/C/opensource/zlog/src/zc_arraylist.h) | C++ | 23 | 15 | 11 | 49 |
| [C/opensource/zlog/src/zc\_defs.h](/C/opensource/zlog/src/zc_defs.h) | C++ | 8 | 14 | 4 | 26 |
| [C/opensource/zlog/src/zc\_hashtable.c](/C/opensource/zlog/src/zc_hashtable.c) | C | 264 | 16 | 58 | 338 |
| [C/opensource/zlog/src/zc\_hashtable.h](/C/opensource/zlog/src/zc_hashtable.h) | C++ | 32 | 14 | 11 | 57 |
| [C/opensource/zlog/src/zc\_profile.c](/C/opensource/zlog/src/zc_profile.c) | C | 69 | 17 | 14 | 100 |
| [C/opensource/zlog/src/zc\_profile.h](/C/opensource/zlog/src/zc_profile.h) | C++ | 37 | 14 | 10 | 61 |
| [C/opensource/zlog/src/zc\_util.c](/C/opensource/zlog/src/zc_util.c) | C | 112 | 18 | 24 | 154 |
| [C/opensource/zlog/src/zc\_util.h](/C/opensource/zlog/src/zc_util.h) | C++ | 7 | 14 | 4 | 25 |
| [C/opensource/zlog/src/zc\_xplatform.h](/C/opensource/zlog/src/zc_xplatform.h) | C++ | 41 | 16 | 16 | 73 |
| [C/opensource/zlog/src/zlog-chk-conf.c](/C/opensource/zlog/src/zlog-chk-conf.c) | C | 51 | 14 | 13 | 78 |
| [C/opensource/zlog/src/zlog.c](/C/opensource/zlog/src/zlog.c) | C | 961 | 82 | 171 | 1,214 |
| [C/opensource/zlog/src/zlog.h](/C/opensource/zlog/src/zlog.h) | C++ | 237 | 24 | 29 | 290 |
| [C/opensource/zlog/src/zlog\_win.c](/C/opensource/zlog/src/zlog_win.c) | C | 72 | 5 | 7 | 84 |
| [C/opensource/zlog/src/zlog\_win.h](/C/opensource/zlog/src/zlog_win.h) | C++ | 53 | 21 | 8 | 82 |
| [C/opensource/zlog/test/CMakeLists.txt](/C/opensource/zlog/test/CMakeLists.txt) | cmake | 44 | 0 | 12 | 56 |
| [C/opensource/zlog/test/fuzzers/zlog\_init\_fuzzer.c](/C/opensource/zlog/test/fuzzers/zlog_init_fuzzer.c) | C | 22 | 0 | 5 | 27 |
| [C/opensource/zlog/test/makefile](/C/opensource/zlog/test/makefile) | Makefile | 36 | 0 | 6 | 42 |
| [C/opensource/zlog/test/test\_bitmap.c](/C/opensource/zlog/test/test_bitmap.c) | C | 25 | 19 | 14 | 58 |
| [C/opensource/zlog/test/test\_buf.c](/C/opensource/zlog/test/test_buf.c) | C | 77 | 14 | 20 | 111 |
| [C/opensource/zlog/test/test\_category.c](/C/opensource/zlog/test/test_category.c) | C | 28 | 14 | 10 | 52 |
| [C/opensource/zlog/test/test\_category.conf](/C/opensource/zlog/test/test_category.conf) | Properties | 5 | 0 | 1 | 6 |
| [C/opensource/zlog/test/test\_conf.c](/C/opensource/zlog/test/test_conf.c) | C | 26 | 14 | 10 | 50 |
| [C/opensource/zlog/test/test\_conf.conf](/C/opensource/zlog/test/test_conf.conf) | Properties | 23 | 0 | 8 | 31 |
| [C/opensource/zlog/test/test\_conf2.c](/C/opensource/zlog/test/test_conf2.c) | C | 27 | 14 | 9 | 50 |
| [C/opensource/zlog/test/test\_conf2.conf.h](/C/opensource/zlog/test/test_conf2.conf.h) | C++ | 1 | 0 | 1 | 2 |
| [C/opensource/zlog/test/test\_default.c](/C/opensource/zlog/test/test_default.c) | C | 14 | 14 | 7 | 35 |
| [C/opensource/zlog/test/test\_default.conf](/C/opensource/zlog/test/test_default.conf) | Properties | 2 | 0 | 1 | 3 |
| [C/opensource/zlog/test/test\_enabled.c](/C/opensource/zlog/test/test_enabled.c) | C | 29 | 17 | 10 | 56 |
| [C/opensource/zlog/test/test\_enabled.conf](/C/opensource/zlog/test/test_enabled.conf) | Properties | 6 | 0 | 1 | 7 |
| [C/opensource/zlog/test/test\_enabled.h](/C/opensource/zlog/test/test_enabled.h) | C++ | 11 | 19 | 7 | 37 |
| [C/opensource/zlog/test/test\_hashtable.c](/C/opensource/zlog/test/test_hashtable.c) | C | 36 | 14 | 16 | 66 |
| [C/opensource/zlog/test/test\_hello.c](/C/opensource/zlog/test/test_hello.c) | C | 21 | 14 | 8 | 43 |
| [C/opensource/zlog/test/test\_hello.conf](/C/opensource/zlog/test/test_hello.conf) | Properties | 7 | 0 | 1 | 8 |
| [C/opensource/zlog/test/test\_hex.c](/C/opensource/zlog/test/test_hex.c) | C | 80 | 14 | 26 | 120 |
| [C/opensource/zlog/test/test\_hex.conf](/C/opensource/zlog/test/test_hex.conf) | Properties | 2 | 0 | 1 | 3 |
| [C/opensource/zlog/test/test\_init.2.conf](/C/opensource/zlog/test/test_init.2.conf) | Properties | 10 | 0 | 3 | 13 |
| [C/opensource/zlog/test/test\_init.c](/C/opensource/zlog/test/test_init.c) | C | 42 | 14 | 8 | 64 |
| [C/opensource/zlog/test/test\_init.conf](/C/opensource/zlog/test/test_init.conf) | Properties | 7 | 0 | 2 | 9 |
| [C/opensource/zlog/test/test\_leak.2.conf](/C/opensource/zlog/test/test_leak.2.conf) | Properties | 7 | 0 | 2 | 9 |
| [C/opensource/zlog/test/test\_leak.c](/C/opensource/zlog/test/test_leak.c) | C | 41 | 15 | 8 | 64 |
| [C/opensource/zlog/test/test\_leak.conf](/C/opensource/zlog/test/test_leak.conf) | Properties | 10 | 0 | 3 | 13 |
| [C/opensource/zlog/test/test\_level.c](/C/opensource/zlog/test/test_level.c) | C | 23 | 14 | 8 | 45 |
| [C/opensource/zlog/test/test\_level.conf](/C/opensource/zlog/test/test_level.conf) | Properties | 6 | 0 | 1 | 7 |
| [C/opensource/zlog/test/test\_level.h](/C/opensource/zlog/test/test_level.h) | C++ | 10 | 19 | 6 | 35 |
| [C/opensource/zlog/test/test\_longlog.c](/C/opensource/zlog/test/test_longlog.c) | C | 49 | 14 | 11 | 74 |
| [C/opensource/zlog/test/test\_longlog.conf](/C/opensource/zlog/test/test_longlog.conf) | Properties | 8 | 2 | 3 | 13 |
| [C/opensource/zlog/test/test\_mdc.c](/C/opensource/zlog/test/test_mdc.c) | C | 29 | 14 | 14 | 57 |
| [C/opensource/zlog/test/test\_mdc.conf](/C/opensource/zlog/test/test_mdc.conf) | Properties | 4 | 0 | 1 | 5 |
| [C/opensource/zlog/test/test\_multithread.c](/C/opensource/zlog/test/test_multithread.c) | C | 157 | 23 | 36 | 216 |
| [C/opensource/zlog/test/test\_multithread.conf](/C/opensource/zlog/test/test_multithread.conf) | Properties | 14 | 0 | 1 | 15 |
| [C/opensource/zlog/test/test\_pipe.c](/C/opensource/zlog/test/test_pipe.c) | C | 21 | 14 | 6 | 41 |
| [C/opensource/zlog/test/test\_pipe.conf](/C/opensource/zlog/test/test_pipe.conf) | Properties | 4 | 0 | 1 | 5 |
| [C/opensource/zlog/test/test\_press\_syslog.c](/C/opensource/zlog/test/test_press_syslog.c) | C | 41 | 14 | 15 | 70 |
| [C/opensource/zlog/test/test\_press\_write.c](/C/opensource/zlog/test/test_press_write.c) | C | 57 | 18 | 20 | 95 |
| [C/opensource/zlog/test/test\_press\_write2.c](/C/opensource/zlog/test/test_press_write2.c) | C | 59 | 17 | 20 | 96 |
| [C/opensource/zlog/test/test\_press\_zlog.c](/C/opensource/zlog/test/test_press_zlog.c) | C | 65 | 14 | 18 | 97 |
| [C/opensource/zlog/test/test\_press\_zlog.conf](/C/opensource/zlog/test/test_press_zlog.conf) | Properties | 4 | 7 | 4 | 15 |
| [C/opensource/zlog/test/test\_press\_zlog2.c](/C/opensource/zlog/test/test_press_zlog2.c) | C | 64 | 14 | 19 | 97 |
| [C/opensource/zlog/test/test\_press\_zlog2.conf](/C/opensource/zlog/test/test_press_zlog2.conf) | Properties | 13 | 0 | 2 | 15 |
| [C/opensource/zlog/test/test\_profile.c](/C/opensource/zlog/test/test_profile.c) | C | 15 | 14 | 8 | 37 |
| [C/opensource/zlog/test/test\_profile.conf](/C/opensource/zlog/test/test_profile.conf) | Properties | 4 | 0 | 1 | 5 |
| [C/opensource/zlog/test/test\_prompt.c](/C/opensource/zlog/test/test_prompt.c) | C | 33 | 15 | 10 | 58 |
| [C/opensource/zlog/test/test\_prompt.conf](/C/opensource/zlog/test/test_prompt.conf) | Properties | 10 | 0 | 3 | 13 |
| [C/opensource/zlog/test/test\_record.c](/C/opensource/zlog/test/test_record.c) | C | 27 | 14 | 8 | 49 |
| [C/opensource/zlog/test/test\_record.conf](/C/opensource/zlog/test/test_record.conf) | Properties | 4 | 0 | 1 | 5 |
| [C/opensource/zlog/test/test\_syslog.c](/C/opensource/zlog/test/test_syslog.c) | C | 22 | 14 | 8 | 44 |
| [C/opensource/zlog/test/test\_syslog.conf](/C/opensource/zlog/test/test_syslog.conf) | Properties | 13 | 0 | 4 | 17 |
| [C/opensource/zlog/test/test\_tmp.c](/C/opensource/zlog/test/test_tmp.c) | C | 26 | 15 | 11 | 52 |
| [C/opensource/zlog/test/test\_tmp.conf](/C/opensource/zlog/test/test_tmp.conf) | Properties | 11 | 0 | 3 | 14 |
| [C/opensource/zlog/test/val.sh](/C/opensource/zlog/test/val.sh) | Shell Script | 4 | 0 | 3 | 7 |
| [C/opensource/zlog/tools/mk\_targz.sh](/C/opensource/zlog/tools/mk_targz.sh) | Shell Script | 17 | 1 | 4 | 22 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)