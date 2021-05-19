using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;

namespace DBTest
{
    class TableAccessor : ICollection<RowAccessor>
    {
        private List<RowAccessor> _row_list;
        private List<RowAccessor> _commited_row_list;

        public TableAccessor()
        {
            _row_list = new List<RowAccessor>();
            _commited_row_list = new List<RowAccessor>();
        }

        public void Add(RowAccessor item)
        {
            if (IsReadOnly)
                throw new ReadOnlyException();

            _row_list.Add(item);
        }

        public void Clear()
        {
            _row_list.Clear();
        }

        public bool Contains(RowAccessor item)
        {
            return _row_list.Contains(item);
        }

        public void CopyTo(RowAccessor[] array, int arrayIndex)
        {
            if (IsReadOnly)
                throw new ReadOnlyException();

            _row_list.CopyTo(array, arrayIndex);
        }

        public int Count
        {
            get
            {
                return _row_list.Count;
            }
        }

        public bool IsReadOnly
        {
            get;
            set;
        }

        public bool Remove(RowAccessor item)
        {
            if (IsReadOnly)
                throw new ReadOnlyException();

            if (this.Contains(item))
                return _row_list.Remove(item);
            else
                return false;
        }

        public IEnumerator<RowAccessor> GetEnumerator()
        {
            for (int i = 0; i < _row_list.Count; i++)
            {
                yield return _row_list[i];
            }
            yield break;
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        public void RevertChanges()
        {
            if (IsReadOnly)
                throw new ReadOnlyException();

            if (_commited_row_list.Count == 0)
                return;

            System.Threading.Monitor.Enter(_row_list);

            _row_list.Clear();
            foreach (var row in _commited_row_list)
                _row_list.Add(row);

            System.Threading.Monitor.Exit(_row_list);
        }

        public void AcceptChanges()
        {
            if (IsReadOnly)
                throw new ReadOnlyException();

            System.Threading.Monitor.Enter(_row_list);

            _commited_row_list.Clear();
            foreach (var row in _row_list)
                _commited_row_list.Add(row);

            System.Threading.Monitor.Exit(_row_list);
        }
    }

    class RowAccessor
    {
        private string _IID;
        public string IID
        {
            get
            {
                return _IID;
            }
            set
            {
                _IID = value;
            }
        }

        private string _PID;
        public string PID
        {
            get
            {
                return _PID;
            }
            set
            {
                _PID = value;
            }
        }

        private string _INAME;
        public string INAME
        {
            get
            {
                return _INAME;
            }
            set
            {
                _INAME = value;
            }
        }

        private string _DETAILS;
        public string DETAILS
        {
            get
            {
                return _DETAILS;
            }
            set
            {
                _DETAILS = value;
            }
        }
    }

    class CustomTableAdapter
    {

    }
}