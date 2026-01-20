
Ce fichier s'adresse au personnel de l'université qui voudrait mettre à jour le site.

# Modification de l'adresse auxquels sont envoyés les emails
- passe par le site: https://formsubmit.co/ 
- modifier le div avec id "foorter-question-window" dans le fichier `layouts/partials/custom-footer.html`

# Redirection du site vers la bonne addresse
On utilise un fichier `.htaccess` (dans `/static`) pour toujours rediriger vers l'adresse `https://monge.univ-eiffel.fr` .