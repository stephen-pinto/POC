//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Text;

#pragma warning disable 168
namespace DBTest.FinalStructure2
{
    public class TempDataSet
    {
        public class TempTableDataTable : System.Data.TypedTableBase<TempTableDataRow>
        {
            public System.Data.DataColumn fieldCOLUMN_ONE = null;
            public System.Data.DataColumn fieldCOLUMN_TWO = null;
            public System.Data.DataColumn fieldCOLUMN_THREE = null;
            public System.Data.DataColumn fieldCOLUMN_FOUR = null;

            public TempTableDataTable()
            {
                this.TableName = "TEMP_TABLE";
                this.BeginInit();
                this.InitClass();
                this.EndInit();
            }

            public TempTableDataTable(System.Data.DataTable table)
            {
                this.TableName = table.TableName;

                if (table.CaseSensitive != table.DataSet.CaseSensitive)
                    this.CaseSensitive = table.CaseSensitive;
                if (table.Locale.ToString() != table.DataSet.Locale.ToString())
                    this.Locale = table.Locale;
                if (table.Namespace != table.DataSet.Namespace)
                    this.Namespace = table.Namespace;

                this.Prefix = table.Prefix;
                this.MinimumCapacity = table.MinimumCapacity;
            }

            protected TempTableDataTable(System.Runtime.Serialization.SerializationInfo info, System.Runtime.Serialization.StreamingContext context) :
                base(info, context)
            {
                this.InitVars();
            }

            public int Count
            {
                get
                {
                    return this.Rows.Count;
                }
            }

            public TempTableDataRow this[int indx]
            {
                get
                {
                    return ((TempTableDataRow)(this.Rows[indx]));
                }
            }

            public void AddTempTableRow(TempTableDataRow row)
            {
                this.Rows.Add(row);
            }

            public TempTableDataRow AddTempTableRow(int COLUMN_ONE, string COLUMN_TWO, string COLUMN_THREE, float COLUMN_FOUR)
            {
                System.Data.DataRow DRow = this.NewRow();
                TempTableDataRow row = (TempTableDataRow)(DRow);
                object[] colValuesArray = new object[] 
                {
                    COLUMN_ONE,
                    COLUMN_TWO,
                    COLUMN_THREE,
                    COLUMN_FOUR
                };
                row.ItemArray = colValuesArray;
                this.Rows.Add(row);
                return row;
            }

            private void InitVars()
            {
                this.fieldCOLUMN_ONE = base.Columns["COLUMN_ONE"];
                this.fieldCOLUMN_TWO = base.Columns["COLUMN_TWO"];
                this.fieldCOLUMN_THREE = base.Columns["COLUMN_THREE"];
                this.fieldCOLUMN_FOUR = base.Columns["COLUMN_FOUR"];
            }

            private void InitClass()
            {
                this.fieldCOLUMN_ONE = new System.Data.DataColumn("COLUMN_ONE", typeof(int), null, System.Data.MappingType.Element);
                base.Columns.Add(this.fieldCOLUMN_ONE);
                this.fieldCOLUMN_TWO = new System.Data.DataColumn("COLUMN_TWO", typeof(string), null, System.Data.MappingType.Element);
                base.Columns.Add(this.fieldCOLUMN_TWO);
                this.fieldCOLUMN_THREE = new System.Data.DataColumn("COLUMN_THREE", typeof(string), null, System.Data.MappingType.Element);
                base.Columns.Add(this.fieldCOLUMN_THREE);
                this.fieldCOLUMN_FOUR = new System.Data.DataColumn("COLUMN_FOUR", typeof(float), null, System.Data.MappingType.Element);
                base.Columns.Add(this.fieldCOLUMN_FOUR);
                //this.Constraints.Add(new System.Data.UniqueConstraint("Constraint1", new System.Data.DataColumn[] { this.fieldCOLUMN_ONE }, true));
                this.fieldCOLUMN_ONE.Unique = true;
                this.fieldCOLUMN_ONE.AllowDBNull = false;
                this.fieldCOLUMN_TWO.MaxLength = 20;
                this.fieldCOLUMN_THREE.MaxLength = 50;
            }


            public TempTableDataRow NewTempTableRow()
            {
                return ((TempTableDataRow)this.NewRow());
            }

            protected override System.Data.DataRow NewRowFromBuilder(System.Data.DataRowBuilder builder)
            {
                return new TempTableDataRow(builder);
            }

            protected override System.Type GetRowType()
            {
                return typeof(TempTableDataRow);
            }

            public override System.Data.DataTable Clone()
            {
                TempTableDataTable cln = ((TempTableDataTable)base.Clone());
                cln.InitVars();
                return cln;
            }

            protected override System.Data.DataTable CreateInstance()
            {
                return new TempTableDataTable();
            }
        }

        public class TempTableDataRow : System.Data.DataRow
        {
            private TempTableDataTable tableTempTable;

            internal TempTableDataRow(System.Data.DataRowBuilder rb)
                : base(rb)
            {
                this.tableTempTable = ((TempTableDataTable)(this.Table));
            }

            public int COLUMN_ONE
            {
                get
                {
                    //A primary key field can never be null so we don't check for DBNull here.
                    return (int)(this[this.tableTempTable.fieldCOLUMN_ONE]);
                }
                set
                {
                    this[this.tableTempTable.fieldCOLUMN_ONE] = value;
                }
            }

            public string COLUMN_TWO
            {
                get
                {
                    try
                    {
                        return (string)(this[this.tableTempTable.fieldCOLUMN_TWO]);
                    }
                    catch (global::System.InvalidCastException excptn)
                    {
                        return null;
                    }
                }
                set
                {
                    this[this.tableTempTable.fieldCOLUMN_TWO] = value;
                }
            }

            public string COLUMN_THREE
            {
                get
                {
                    try
                    {
                        return (string)(this[this.tableTempTable.fieldCOLUMN_THREE]);
                    }
                    catch (global::System.InvalidCastException excptn)
                    {
                        return null;
                    }
                }
                set
                {
                    this[this.tableTempTable.fieldCOLUMN_THREE] = value;
                }
            }


            public float COLUMN_FOUR
            {
                get
                {
                    try
                    {
                        return (float)(this[this.tableTempTable.fieldCOLUMN_FOUR]);
                    }
                    catch (global::System.InvalidCastException excptn)
                    {
                        return float.NegativeInfinity;
                    }
                }
                set
                {
                    this[this.tableTempTable.fieldCOLUMN_FOUR] = value;
                }
            }
        }
    }
}
#pragma warning restore 168