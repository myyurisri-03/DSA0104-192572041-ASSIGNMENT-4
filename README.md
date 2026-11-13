# DSA01-<RegisterNumber>-Assignment4

**Course:** Object Oriented Programming with C++ (DSA01) | **CO4:** Designing Reusable Class Hierarchies

| | |
|---|---|
| Name | [Your name] |
| Register Number | [Your register number] |
| Compiler | g++ 13.3.0 (Ubuntu 24.04) |
| Compile command | `g++ -std=c++17 -Wall -Wextra <file>.cpp -o <name>` |
| Sanitizer command | `g++ -std=c++17 -Wall -Wextra -fsanitize=address -g <file>.cpp -o <name>` |

> Before submitting: replace the placeholders above, re-run `bash run_all.sh` on **your own machine**,
> compare with the stored outputs, add your screenshots to each Q folder, and make at least one Git commit per task
> (for example `git commit -m "Q4: account defects repaired"`).
> For the two *Predict the Output* tasks in Q2, Q3 and Q4, write your own prediction in the report BEFORE you run the program.

## How to run

```bash
bash run_all.sh        # builds and runs everything; writes compile_*.txt and output_*.txt in each Q folder
# or one program by hand:
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g Q4/task4_fixed.cpp -o task4_fixed && ./task4_fixed
# Q6 programs include vehicles.h from the same folder:
g++ -std=c++17 -Wall -Wextra -IQ6 Q6/task6_fleet.cpp -o fleet && ./fleet
```
Timings differ from machine to machine, so your numbers will not match the stored ones.

## Folder contents and results

### Q1 – Class design review (payroll)
| File | Purpose | Result |
|---|---|---|
| `task1_staff.cpp` | Repaired hierarchy: abstract `Staff`, `SalariedStaff`, `Professor`, `LabAssistant`, `GuestFaculty`; `DA_RATE` constant; one loop over all staff | Pay: 128600, 42600, 60000; total 231200 |
| `task1_single_class.cpp` | Alternative: one class with type field and `switch` | Same pay values; every object is 80 bytes (unused fields) |

### Q2 – From requirement to hierarchy
| File | Purpose | Result |
|---|---|---|
| `predict_diamond.cpp` | Predict-the-output (virtual base) | `Person Student Staff TA ` |
| `predict_diamond_nonvirtual.cpp` | `virtual` removed | `Person Student Person Staff TA ` (Person built twice, compiles without messages) |
| `ambiguity_demo.cpp` | `ta.name` with and without virtual | Works; with `-DNONVIRTUAL`: `request for member 'name' is ambiguous` |
| `people_classes.cpp` | Task 2.3 class declarations, TA and ResearchScholar | Prints both records |
| `access_check.cpp` | Verifies the access table (`-DE1` … `-DE5` produce each access error) | `compile_access_E1..E5.txt` hold the errors |
| `composition_sizeof.cpp` | Alternative: composition vs inheritance | sizeof: virtual 168, non-virtual 224, composition 224 |

### Q3 – Constructors in derived classes and member classes
| File | Purpose | Result |
|---|---|---|
| `task3_construction.cpp` | Constructors with initializer lists, `Address` and `Course` member classes, trace | TA: `Address Person Course Student Staff TA \| ~TA ~Staff ~Student ~Course ~Person ~Address` |
| `task3_nonvirtual_experiment.cpp` | Task 3.4: with and without `virtual` | Virtual: Person built once, sizeof 72; non-virtual: twice, sizeof 96 |
| `predict_engine.cpp` | Predict-the-output | `Vehicle Engine Car \| ~Car ~Engine ~Vehicle ` |
| `complete_student.cpp` | Complete-the-code (TODO 1) | `192311001 Kavya (19) Salem-636001` |
| `complete_student_swapped.cpp` | Swapped initializer order | `-Wreorder` warning (see `compile_complete_student_swapped.txt`) |
| `pointer_member.cpp` | Alternative: `Address*` member | Needs deep copy constructor, copy assignment, destructor; clean under ASan |

### Q4 – Pointers to derived classes: forensics
| File | Purpose | Result |
|---|---|---|
| `task4_buggy.cpp` | Defective program with destructor messages | Prints 3.5 and 3.5; `~SeniorAccount` never runs for the heap object; `copy.rate()` is 3.5 (`output_task4_buggy_plain.txt`) |
| ASan runs | `output_task4_buggy.txt`, `output_task4_buggy_leak_only.txt` | `new-delete-type-mismatch`; with that check off: LeakSanitizer reports 800 bytes leaked |
| `task4_fixed.cpp` | Repair: virtual function, virtual destructor, `override`, deleted copy | Prints 3.5 and 4; both destructors run; clean under ASan |
| `task4_fixed.cpp -DTRY_SLICE` | Slicing now blocked | Compile error: use of deleted function `Account::Account(const Account&)` |
| `predict_account.cpp` | Predict-the-output | `3.5 4 3.5` |
| `task4_unique_ptr.cpp` | Alternative: `vector<unique_ptr<Account>>` | Same behaviour, no manual `delete` |

### Q5 – Pointers to objects and `this`
| File | Purpose | Result |
|---|---|---|
| `task5_cart.cpp` | Complete-the-code (TODO 1, 2) | `324.00` |
| `task5_return_by_value.cpp` | `add()` returning `Cart` instead of `Cart&` | `240.00` (chain works on temporary copies; rice and discount are lost) |
| `task5_four_ways.cpp` | Name, pointer, reference, `new`/`delete`; `this`; array-of-pointers search | Highest total: Asha = 324.00 |
| `task5_vector.cpp` | Alternative: `vector<Cart>` | sizeof(Cart)=408; element 0 moves when the vector grows |

### Q6 – Vehicle rental fleet
| File | Purpose | Result |
|---|---|---|
| `vehicles.h` | Hierarchy: abstract `Vehicle` → `Bicycle`, `MotorVehicle` → `TwoWheeler`, `Car` → `ElectricCar`; member class `ServiceDate` | |
| `task6_fleet.cpp` | Rent, return with late charge, list | Bills: 300, 1365, 3450, 5450 |
| `task6_extension.cpp` | New `ElectricBus` added without changing `vehicles.h` | Bus bill 15960 |
| `task6_switch.cpp` | Alternative: one class with `switch` | Same bills; sizeof(Vehicle)=80 for every object |
| `task6_bench.cpp` | 10,000,000 charge calls: virtual vs switch | About equal at `-O2` |

## Notes
- `compile_*.txt` holds compiler warnings or errors; `output_*.txt` holds program output and exit code.
- Programs that are meant to fail (`access_E1..E5`, `ambiguity_nonvirtual`, `task4_slice_blocked`) have only a compile error file.
