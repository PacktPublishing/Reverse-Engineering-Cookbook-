// app.js
document
  .getElementById('fetchDataButton')
  .addEventListener('click', function () {
    alert('Button clicked! Fetching data...');
    fetchData();
  });

function fetchData() {
  fetch('https://jsonplaceholder.typicode.com/posts/1')
    .then((response) => response.json())
    .then((data) => {
      console.log(data);
      // Demonstrating the use of eval
      const code = "console.log('Data fetched: ' + JSON.stringify(data));";
      eval(code); // Warning: eval can execute arbitrary code
    })
    .catch((error) => console.error('Error fetching data:', error));
}

// Demonstrating setTimeout usage
setTimeout(() => {
  alert('This message appears after 3 seconds!');
}, 3000); // Executes after 3000 milliseconds (3 seconds)
