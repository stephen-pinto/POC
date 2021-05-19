//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

namespace DBTest
{
    //class DataColumnExtTyped<T> : DataColumnExt
    //{
    //    public T DataValueTypedExt
    //    {
    //        get
    //        {
    //            if (this.DataValueExt == null || this.DataValueExt == System.DBNull.Value)
    //                throw new ValueNullException("Value for DataColumn is null or DBNull");

    //            return (T) this.DataValueExt;
    //        }
    //        set
    //        {
    //            this.DataValueExt = value;
    //        }
    //    }

    //    public T DefaultTypedValueExt
    //    {
    //        get
    //        {
    //            if (this.DefaultValue == System.DBNull.Value || this.DefaultValue == null)
    //                throw new ValueNullException("Value for DataColumn is null or DBNull");
    //            else
    //                return (T)this.DefaultValue;
    //        }
    //        set
    //        {
    //            this.DefaultValue = value;
    //        }
    //    }

    //    public DataColumnExtTyped(string column_name, T? value = null, T? default_value = null, int length_limit = 0) :
    //        base(column_name, value.GetType(), value.ToString())
    //    {
    //        if(value.HasValue)
    //            this._DataValueExt = value.Value;
            
    //        this.DataType = value.GetType();
    //        if (default_value.HasValue)
    //            this.DefaultValue = default_value.Value;
    //        else
    //            this.DefaultValue = System.DBNull.Value;
    //        this.MaxLength = length_limit;
    //    }
    //}

    //class DataColumnExt : System.Data.DataColumn
    //{
    //    /*Private members and properties*/

    //    protected object _DataValueExt = System.DBNull.Value;

    //    /**/

    //    /*Public members and properties*/

    //    public delegate void DataColumnExtValueChangedHandler1(object sender);
    //    public event DataColumnExtValueChangedHandler1 ColumnValueChanged1;
        
    //    public delegate void DataColumnExtValueChangedHandler2(object sender, DataColumnExt changed_from);
    //    public event DataColumnExtValueChangedHandler2 ColumnValueChanged2;

    //    public DataColumnExt(string column_name, object value, object default_value = null, int length_limit = 0) :
    //        base(column_name, value.GetType(), value.ToString())
    //    {
    //        this._DataValueExt = value;
    //        this.DataType = value.GetType();
    //        this.DefaultValue = default_value;
    //        this.MaxLength = length_limit;
    //    }

    //    public object DataValueExt
    //    {
    //        get
    //        {
    //            return this._DataValueExt;
    //        }
    //        set
    //        {
    //            if ((this.DataType == typeof(string)) && (this.MaxLength == 0 && ((string)value).Length > this.MaxLength))
    //                throw new ValueLengthException("Length for column exceeded " + this.MaxLength + " bytes...");
    //            else
    //            {
    //                object temp = this._DataValueExt;
    //                this._DataValueExt = value;
    //                if (ColumnValueChanged1 != null)
    //                    ColumnValueChanged1(this);
    //                if (ColumnValueChanged2 != null)
    //                    ColumnValueChanged2(this, new DataColumnExt(this.ColumnName, temp));
    //            }
    //        }
    //    }


    //    public object DefaultValueExt
    //    {
    //        get
    //        {
    //            return this.DefaultValue;
    //        }
    //        set
    //        {
    //            if ((this.DataType == typeof(string)) && (this.MaxLength == 0 && ((string)value).Length > this.MaxLength))
    //                throw new ValueLengthException("Length for column exceeded " + this.MaxLength + " bytes...");
    //            else
    //                this.DefaultValue = value;
    //        }
    //    }




    //    /**/
    //}
}
