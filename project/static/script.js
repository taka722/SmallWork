
document.addEventListener('DOMContentLoaded', function() {
    var darkModeToggle = document.getElementById('dark-mode-toggle');

    // Apply the saved theme on load
    if (localStorage.getItem('darkMode') === 'true') {
        document.body.classList.add('dark-mode');
    }

    if (darkModeToggle) {
        darkModeToggle.addEventListener('click', function() {
            var isDarkMode = document.body.classList.toggle('dark-mode');
            localStorage.setItem('darkMode', isDarkMode);
        });
    }



    // Check for the compliment element
    var complimentElement = document.getElementById('compliment');
    if (complimentElement) {
        // Wait for 5 seconds, then add the fade-out class
        setTimeout(function() {
            complimentElement.classList.add('fade-out');

            // Optional: Remove the element from the DOM after 2 seconds
            setTimeout(function() {
                complimentElement.style.display = 'none';
            }, 2000); // 2000 ms = 2 seconds
        }, 5000); // 5000 ms = 5 seconds
    }
});


function validateTitle(input) {
    var titleError = document.getElementById('titleError');
    if (input.value.length < 3) {
        titleError.style.display = 'block';
    } else {
        titleError.style.display = 'none';
    }
}
