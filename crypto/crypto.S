.globl get_id_aa64isar0_el1

get_id_aa64isar0_el1:
    mrs x0, id_aa64isar0_el1
    ret