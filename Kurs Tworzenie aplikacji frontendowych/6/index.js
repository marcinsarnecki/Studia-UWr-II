function cloneDeep(obj) {
  if (obj instanceof Date) //data
    return new Date(obj.getTime())
  if (obj === null || typeof (obj) !== 'object') //primitive
      return obj;
  const newObject = {}
  for(const it of Object.entries(obj)) {
    const [key, value] = it;
    newObject[key] = cloneDeep(value);
  }
  return newObject;
}

const user = {
  name: "Alice",
  surname: "Young",
  dates: {
    birthDate: new Date(1995, 10, 28)
  },
  contact: {
    phone: '111-111-111',
    address: {
      city: "London",
    }
  }
};

const userCp = cloneDeep(user);

console.log("user.dates.birthDate instanceof Date", user.dates.birthDate instanceof Date);
console.log("userCp.dates.birthDate instanceof Date", userCp.dates.birthDate instanceof Date);

user.name = "John";
user.surname = "White";
user.dates.birthDate = new Date(1999, 11, 11);
user.contact.phone = '222-222-222';
user.contact.address.city = 'New York'

console.log(user);
console.log(userCp);