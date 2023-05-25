use pyo3::prelude::*;

/// Formats the sum of two numbers as string.
#[pyfunction]
fn pow_mod(mut x: u64, mut y: u64, z: u64) -> u64 {
    let mut number:u64 =1;

    while y!=0 {
        if y&1!=0 {
            number = number * x % z;
        }
        y >>= 1;
        x = (x*x)%z;
    }

    return number;
    
}


// unsigned long long pow_mod(long long x, long long y, const long long z)
// {
//     unsigned long long number = 1;
//     while (y)
//     {
//         if (y & 1)  /* is_even */
//             number = number * x % z;
//         y >>= 1;  /* diviide 2 */
//         x = (unsigned long long)x * x % z;  
//     }
//     return number;
// }


/// A Python module implemented in Rust.
#[pymodule]
fn my_prime(_py: Python, m: &PyModule) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(pow_mod, m)?)?;
    Ok(())
}