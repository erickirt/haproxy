#ifndef _HAPROXY_CPU_TOPO_H
#define _HAPROXY_CPU_TOPO_H

#include <haproxy/api.h>
#include <haproxy/cpuset-t.h>
#include <haproxy/cpu_topo-t.h>

extern int cpu_topo_maxcpus;
extern int cpu_topo_lastcpu;
extern struct ha_cpu_topo *ha_cpu_topo;

/* non-zero if we're certain that taskset or similar was used to force CPUs */
extern int cpu_mask_forced;

/* Detects CPUs that are online on the system. It may rely on FS access (e.g.
 * /sys on Linux). Returns the number of CPUs detected or 0 if the detection
 * failed.
 */
int ha_cpuset_detect_online(struct hap_cpuset *set);

/* Detects the CPUs that will be used based on the ones the process is bound to.
 * Returns non-zero on success, zero on failure. Note that it may not be
 * performed in the function above because some calls may rely on other items
 * being allocated (e.g. trash).
 */
int cpu_detect_usable(void);

/* detect the CPU topology based on info in /sys */
int cpu_detect_topology(void);

/* Detects CPUs that are bound to the current process. Returns the number of
 * CPUs detected or 0 if the detection failed.
 */
int ha_cpuset_detect_bound(struct hap_cpuset *set);

/* Returns true if at least one cpu-map directive was configured, otherwise
 * false.
 */
int cpu_map_configured(void);

/* Dump the CPU topology <topo> for up to cpu_topo_maxcpus CPUs for
 * debugging purposes. Offline CPUs are skipped.
 */
void cpu_dump_topology(const struct ha_cpu_topo *topo);

/* re-order a CPU topology array by CPU index only, to undo the function above,
 * in case other calls need to be made on top of this.
 */
void cpu_reorder_by_index(struct ha_cpu_topo *topo, int entries);

/* Functions used by qsort to compare hardware CPUs (not meant to be used from
 * outside cpu_topo).
 */
int _cmp_cpu_index(const void *a, const void *b);

#endif /* _HAPROXY_CPU_TOPO_H */
