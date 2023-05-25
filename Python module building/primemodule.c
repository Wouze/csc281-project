#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Python.h"
#include <omp.h>


int cis_prime(int n)
{
  int last = (int) sqrt(n) + 1; 

  for (int j = 2; j <= last; ++j)
    if (n % j == 0)
      return 0;

  return 1;
}

long long cpow_mod2(long long g, long long exp, long long n)
{
    if (exp == 0)
        return 1;
    if (exp == 1)
        return g % n;
    if (exp == 2)
        return (g * g) % n;

    return cpow_mod2( cpow_mod2(g, exp%2, n) * cpow_mod2( cpow_mod2(g, exp>>1, n)*cpow_mod2(g, exp>>1, n), 1, n ), 1, n  );
}

long long cpow_mod(long long x, long long y, long long z)
{
    long long number = 1;
    while (y)
    {
        if (y & 1)  /* is_even */
            number = number * x % z;
        y >>= 1;  /* diviide 2 */
        x = (unsigned long long)x * x % z;  
    }
    return number;
}

int cis_primitive_root(int g, int n)
{
    int i;

    for (i = 1; i < n - 1; i++)
    {
        if (cpow_mod(g, i, n) == 1)
            return 0;
    }

    return 1;
}


int main()
{   
    clock_t t;
    t = clock();
    
    int p = 5003;
    
    int count =0;
    for (int i =1; i < p; i++)
    {
        if (cis_primitive_root(i, p)){
            count++;
            // printf("%d Is primitive root to %d\n", i, p);   
        }
    }

    printf("roots: %d\n", count);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("took %f seconds to execute \n", time_taken);
    
    return 0;
}





static PyObject* is_prime(PyObject* self, PyObject* args){
    int number, sts;
    
    if (!PyArg_ParseTuple(args, "i", &number))
        return NULL;
    
    sts = cis_prime(number);
    return PyBool_FromLong(sts);
}


static PyObject* pow_mod(PyObject* self, PyObject* args){
    long x, y, z;
    unsigned long long sts;
    
    if (!PyArg_ParseTuple(args, "lll", &x, &y, &z))
        return NULL;
    
    sts = cpow_mod(x, y, z);
    return PyLong_FromLongLong(sts);
}

static PyObject* pow_mod2(PyObject* self, PyObject* args){
    long x, y, z;
    long long sts;
    
    if (!PyArg_ParseTuple(args, "lll", &x, &y, &z))
        return NULL;
    
    sts = cpow_mod(x, y, z);
    return PyLong_FromLongLong(sts);
}

static PyObject* is_primitive_root(PyObject* self, PyObject* args){
    int g, n, sts;
    
    if (!PyArg_ParseTuple(args, "ii", &g, &n))
        return NULL;
    
    sts = cis_primitive_root(g, n);
    return PyBool_FromLong(sts);
}

static PyObject* get_all_primitive_roots(PyObject* self, PyObject* args){
    int p;
    
    if (!PyArg_ParseTuple(args, "i", &p))
        return NULL;
        
    PyObject* list = PyList_New(0);
    // int ii =0;
    for (long i =1; i < p; i++)
    {
        if (cis_primitive_root(i, p)){
            PyList_Append(list, PyLong_FromLong(i));
            // PyList_SET_ITEM(list, ii++, PyLong_FromLong(i));
        }
    }

    return list;
}

static PyObject* get_all_primitive_roots_loop(PyObject* self, PyObject* args){
    int p;
    
    if (!PyArg_ParseTuple(args, "i", &p))
        return NULL;
    PyObject* list = PyList_New(0);

    if (!cis_prime(p)){
        printf("%d Is not a prime!\n",p);
        return list;
    }

    int o = 1;
    unsigned long long k;
    for (int r = 2; r < p; r++) {
        k = cpow_mod(r, o, p);

        while (k > 1) {
            o++;
            k *= r;
            k %= p;
        }
        if (o == (p - 1)) {
            PyList_Append(list, PyLong_FromLong(r));
        }
        o = 1;
    }

    return list;
}

// static PyObject* get_all_primitive_roots_loop_thread(PyObject* self, PyObject* args){
//     int p;
    
//     if (!PyArg_ParseTuple(args, "i", &p))
//         return NULL;
        
//     PyObject* list = PyList_New(0);


//     PyThreadState *_save;

//     _save = PyEval_SaveThread();
//     int o = 1;
//     unsigned long long k;
//     #pragma omp parallel for private(o) reduction(+:list)
//     for (int r = 2; r < p; r++) {
//         k = cpow_mod(r, o, p);

//         while (k > 1) {
//             o++;
//             k *= r;
//             k %= p;
//         }
//         if (o == (p - 1)) {
//             PyList_Append(list, PyLong_FromLong(r));
//         }
//         o = 1;
//     }
//     PyEval_RestoreThread(_save);

//     return list;
// }

static PyObject* version(PyObject* self){
    return Py_BuildValue("s", "Version 0.1");
}

static PyMethodDef MyPrimes[] = {
    {"is_prime", is_prime, METH_VARARGS, "Calculates if the number is prime or not."},
    {"pow_mod", pow_mod, METH_VARARGS, "Calculates (base^power) %% mod efficiently. (Mohammad function)"},
    {"pow_mod2", pow_mod2, METH_VARARGS, "Calculates (base^power) %% mod efficiently. (Mosaed function)"},
    {"is_primitive_root", is_primitive_root, METH_VARARGS, "Checks if x is a primitive root for y."},
    {"get_all_primitive_roots", get_all_primitive_roots, METH_VARARGS, "Returns all primitive roots from p."},
    {"get_all_primitive_roots_loop", get_all_primitive_roots_loop, METH_VARARGS, "Returns all primitive roots from p."},
    // {"get_all_primitive_roots_loop_thread", get_all_primitive_roots_loop_thread, METH_VARARGS, "Returns all primitive roots from p (threaded)."},
    {"version", (PyCFunction)version, METH_NOARGS, "Returns the version of the module."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef MyPrime = {
    PyModuleDef_HEAD_INIT,
    "MyPrime",
    "Prime calculations module",
    -1, // global state
    MyPrimes,
};

PyMODINIT_FUNC PyInit_MyPrime(void)
{
    return PyModule_Create(&MyPrime);   
}




// PRIME website
// int main() {
//     clock_t t;
//     t = clock();
//     int o = 1;
//     int k;
//     // int roots[1000];
//     int z = 0;
//     int theNum = 10006; // Replace with the actual value of theNum

//     for (int r = 2; r < theNum; r++) {
//         k = pow(r, o);
//         k %= theNum;
//         while (k > 1) {
//             o++;
//             k *= r;
//             k %= theNum;
//         }
//         if (o == (theNum - 1)) {
//             // roots[z] = r;
//             z++;
//         }
//         o = 1;
//     }
//     printf("%d has %d primitive roots, and they are \n", theNum, z);
//     z--;

//     t = clock() - t;
//     double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
//     printf("took %f seconds to execute \n", time_taken);
    
//     // for (int y = 0; y < z; y++) {
//     //     printf("%d ", roots[y]);
//     // }

//     return 0;

// }










// JUNKK

// unsigned long pow_mod(unsigned short x, unsigned long y, unsigned short z)
// {
//     unsigned long number = 1;
//     while (y)
//     {
//         if (y & 1)
//             number = number * x % z;
//         y >>= 1;
//         x = (unsigned long long)x * x % z;
//     }
//     return number;
// }

// int is_primitive_root_powmod(unsigned long long g, unsigned long long n)
// {
//     unsigned long long i;

//     for (i = 1; i < n - 1; i++)
//     {
//         if (pow_mod(g, i, n) == 1)
//             return 0;
//     }

//     return 1;
// }
