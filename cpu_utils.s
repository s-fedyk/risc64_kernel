.section .text
.global _get_hart_id
_get_hart_id:
        csrr a0, mhartid
        ret

.global _setup_thread_id
_setup_thread_id:
  csrr a0, mhartid
  mv tp, a0
  ret

.global _get_thread_id
_get_thread_id:
  mv a0, tp
  ret

# return 0 if success, 1 if failure
# a0 should be an address 
.global _try_lock 
_try_lock:
  mv t1, a0
  li a0, 1
  amoswap.w.aq a0, a0, (t1)
  ret

# release lock regardless of if we are holding it
# returns the previous value of the lock
.global _release_lock
_release_lock:
  mv t1, a0
  li a0, 0
  amoswap.w.aq a0, a0, (t1)
  ret

.global _write_sstatus
_write_sstatus:
  csrw sstatus, a0
  ret

.global _read_sstatus
_read_sstatus: 
  csrr a0, sstatus
  ret 

.global _write_mstatus
_write_mstatus:
  csrw mstatus, a0
  ret

.global _read_mstatus
_read_mstatus: 
  csrr a0, mstatus
  ret 

.global _get_interrupt_cause
_get_interrupt_cause:
  csrr a0, ucause
  ret

_get_stimecmp:
  csrr a0, stimecmp 
  ret

_write_stimecmp:
  csrw stimecmp, a0
  ret

.global _get_sie
_get_sie:
  csrr a0, sie
  ret

.global _write_sie
_write_sie:
  csrw sie, a0
  ret

.global _get_mie
_get_mie:
  csrr a0, mie
  ret

.global _write_mie
_write_mie:
  csrw mie, a0
  ret
