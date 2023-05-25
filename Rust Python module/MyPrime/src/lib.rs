use pyo3::{prelude::*, types::PyList};

/// Formats the sum of two numbers as string.
#[pyfunction]
fn pow_mod(mut x: u64, mut y: u64, z: u64) -> u64 {
    let mut number: u64 = 1;

    while y != 0 {
        if y & 1 != 0 {
            number = number * x % z;
        }
        y >>= 1;
        x = (x * x) % z;
    }

    return number;
}

#[pyfunction]
fn is_primitive_root(g: u64, n: u64) -> bool {
    let mut i: u64 = 1;

    while i < n - 1 {
        if pow_mod(g, i, n) == 1 {
            return false;
        }

        i += 1;
    }

    return true;
}

#[pyfunction]
fn get_all_primitive_roots(py: Python, p: u64) -> &PyList {
    let lis: &PyList = PyList::new(py, [0]);
    lis.del_item(0);
    let mut i: u64 = 1;
    while i < p {
        if is_primitive_root(i, p) {
            lis.append(i);
        }

        i += 1;
    }

    return lis;
}

#[pyfunction]
fn get_all_primitive_roots_loop(py: Python, p: u64) -> &PyList {
    let lis: &PyList = PyList::new(py, [0]);
    lis.del_item(0);

    let mut o:u64 = 1;
    let mut k:u64;
    let mut r:u64 =2;
    while r<p {
        k = pow_mod(r, o, p);

        while k > 1 {
            o+=1;
            k *= r;
            k %= p;
        }
        if o == (p - 1) {
            lis.append(r);
        }
        o = 1;
        r+=1;
    }
    return lis;
}

/// A Python module implemented in Rust.
#[pymodule]
fn my_prime(_py: Python, m: &PyModule) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(pow_mod, m)?)?;
    m.add_function(wrap_pyfunction!(is_primitive_root, m)?)?;
    m.add_function(wrap_pyfunction!(get_all_primitive_roots, m)?)?;
    m.add_function(wrap_pyfunction!(get_all_primitive_roots_loop, m)?)?;
    Ok(())
}
