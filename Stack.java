public class Stack extends List {

        public Base pop () {
                return remove (END);
        }

        public Base push (Base element) {
                return insert (element, END);
        }

        public Base top () {
                return view (END);
        }
}
