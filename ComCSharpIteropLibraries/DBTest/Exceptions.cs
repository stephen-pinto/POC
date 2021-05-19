using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DBTest
{
    class ValueNullException : Exception
    {
        public ValueNullException() : base("Value is null") { }
        public ValueNullException(string message) : base(message) { }        
    }

    class ValueLengthException : Exception
    {
        public ValueLengthException() : base("Defined length of value exceeded") { }
        public ValueLengthException(string message) : base(message) { }
    }
}
