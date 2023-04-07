#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define max_prime_factor 32

/**
 * @breif Find the smallest number in his own power that divides a given number
*/

int main() {
	int received_num ,power_times , num_prime = 0, holder_of_recieved, i,
	    smallest_num = 1, bigest_power = 0, primes[max_prime_factor] = { 0 };
	
	scanf("%d", &received_num);
	holder_of_recieved = received_num ;

	// Searching all of the primes numbers and their's power in recievd_num
	for (i = 2; i <= sqrt(received_num); i++) {
		if (holder_of_recieved % i == 0) {
			primes[num_prime] = i;
			power_times = 1;

			/* Build the smallest_num to share the same primes 
			 * with the received_num with a power of 1 */
			smallest_num = smallest_num * primes[num_prime];

			while (holder_of_recieved % i == 0) {
				power_times++;
				holder_of_recieved /= i;
			}
			
			if (power_times > bigest_power) {
				bigest_power = power_times;
			}

			num_prime++;
		}
	}

	// When received_num is prime
	if (received_num == holder_of_recieved) {
		printf("%d\n\n", received_num);
	}

	/* Looking for smallest_num ^ smallest_num, smallest_num share the 
	 * same primes with received_num, remaines to check the power */
	else if (smallest_num > bigest_power) {
		printf("%d\n\n", smallest_num);
	}

	else {
		while (smallest_num < bigest_power) {

			// Increasing the number with the smallest prime  
			smallest_num = smallest_num * primes[0];
		}
		printf("%d\n\n", smallest_num);
	}

	return 0;
}
