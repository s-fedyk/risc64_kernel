.section .text
.global _get_hart_id
_get_hart_id:
        csrr a0, mhartid
        ret
